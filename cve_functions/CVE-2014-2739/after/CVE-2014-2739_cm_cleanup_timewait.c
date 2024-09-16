static void cm_cleanup_timewait(struct cm_timewait_info *timewait_info)
{
	if (timewait_info->inserted_remote_id) {
		rb_erase(&timewait_info->remote_id_node, &cm.remote_id_table);
		timewait_info->inserted_remote_id = 0;
	}

	if (timewait_info->inserted_remote_qp) {
		rb_erase(&timewait_info->remote_qp_node, &cm.remote_qp_table);
		timewait_info->inserted_remote_qp = 0;
	}
}
