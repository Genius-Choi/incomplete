static int rds_tcp_init(void)
{
	int ret;

	rds_tcp_conn_slab = kmem_cache_create("rds_tcp_connection",
					      sizeof(struct rds_tcp_connection),
					      0, 0, NULL);
	if (!rds_tcp_conn_slab) {
		ret = -ENOMEM;
		goto out;
	}

	ret = rds_tcp_recv_init();
	if (ret)
		goto out_slab;

	ret = register_pernet_device(&rds_tcp_net_ops);
	if (ret)
		goto out_recv;

	rds_trans_register(&rds_tcp_transport);

	rds_info_register_func(RDS_INFO_TCP_SOCKETS, rds_tcp_tc_info);
#if IS_ENABLED(CONFIG_IPV6)
	rds_info_register_func(RDS6_INFO_TCP_SOCKETS, rds6_tcp_tc_info);
#endif

	goto out;
out_recv:
	rds_tcp_recv_exit();
out_slab:
	kmem_cache_destroy(rds_tcp_conn_slab);
out:
	return ret;
}
