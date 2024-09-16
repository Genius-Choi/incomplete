static struct cm_timewait_info * cm_insert_remote_id(struct cm_timewait_info
						     *timewait_info)
{
	struct rb_node **link = &cm.remote_id_table.rb_node;
	struct rb_node *parent = NULL;
	struct cm_timewait_info *cur_timewait_info;
	__be64 remote_ca_guid = timewait_info->remote_ca_guid;
	__be32 remote_id = timewait_info->work.remote_id;

	while (*link) {
		parent = *link;
		cur_timewait_info = rb_entry(parent, struct cm_timewait_info,
					     remote_id_node);
		if (be32_lt(remote_id, cur_timewait_info->work.remote_id))
			link = &(*link)->rb_left;
		else if (be32_gt(remote_id, cur_timewait_info->work.remote_id))
			link = &(*link)->rb_right;
		else if (be64_lt(remote_ca_guid, cur_timewait_info->remote_ca_guid))
			link = &(*link)->rb_left;
		else if (be64_gt(remote_ca_guid, cur_timewait_info->remote_ca_guid))
			link = &(*link)->rb_right;
		else
			return cur_timewait_info;
	}
	timewait_info->inserted_remote_id = 1;
	rb_link_node(&timewait_info->remote_id_node, parent, link);
	rb_insert_color(&timewait_info->remote_id_node, &cm.remote_id_table);
	return NULL;
}
