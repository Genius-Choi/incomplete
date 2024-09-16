int o2nm_depend_this_node(void)
{
	int ret = 0;
	struct o2nm_node *local_node;

	local_node = o2nm_get_node_by_num(o2nm_this_node());
	if (!local_node) {
		ret = -EINVAL;
		goto out;
	}

	ret = o2nm_depend_item(&local_node->nd_item);
	o2nm_node_put(local_node);

out:
	return ret;
}
