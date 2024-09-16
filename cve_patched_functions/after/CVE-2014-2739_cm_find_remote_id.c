static struct cm_timewait_info * cm_find_remote_id(__be64 remote_ca_guid,
						   __be32 remote_id)
{
	struct rb_node *node = cm.remote_id_table.rb_node;
	struct cm_timewait_info *timewait_info;

	while (node) {
		timewait_info = rb_entry(node, struct cm_timewait_info,
					 remote_id_node);
		if (be32_lt(remote_id, timewait_info->work.remote_id))
			node = node->rb_left;
		else if (be32_gt(remote_id, timewait_info->work.remote_id))
			node = node->rb_right;
		else if (be64_lt(remote_ca_guid, timewait_info->remote_ca_guid))
			node = node->rb_left;
		else if (be64_gt(remote_ca_guid, timewait_info->remote_ca_guid))
			node = node->rb_right;
		else
			return timewait_info;
	}
	return NULL;
}
