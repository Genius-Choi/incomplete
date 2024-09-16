static int rds_tcp_conn_alloc(struct rds_connection *conn, gfp_t gfp)
{
	struct rds_tcp_connection *tc;
	int i, j;
	int ret = 0;

	for (i = 0; i < RDS_MPATH_WORKERS; i++) {
		tc = kmem_cache_alloc(rds_tcp_conn_slab, gfp);
		if (!tc) {
			ret = -ENOMEM;
			goto fail;
		}
		mutex_init(&tc->t_conn_path_lock);
		tc->t_sock = NULL;
		tc->t_tinc = NULL;
		tc->t_tinc_hdr_rem = sizeof(struct rds_header);
		tc->t_tinc_data_rem = 0;

		conn->c_path[i].cp_transport_data = tc;
		tc->t_cpath = &conn->c_path[i];
		tc->t_tcp_node_detached = true;

		rdsdebug("rds_conn_path [%d] tc %p\n", i,
			 conn->c_path[i].cp_transport_data);
	}
	spin_lock_irq(&rds_tcp_conn_lock);
	for (i = 0; i < RDS_MPATH_WORKERS; i++) {
		tc = conn->c_path[i].cp_transport_data;
		tc->t_tcp_node_detached = false;
		list_add_tail(&tc->t_tcp_node, &rds_tcp_conn_list);
	}
	spin_unlock_irq(&rds_tcp_conn_lock);
fail:
	if (ret) {
		for (j = 0; j < i; j++)
			rds_tcp_conn_free(conn->c_path[j].cp_transport_data);
	}
	return ret;
}
