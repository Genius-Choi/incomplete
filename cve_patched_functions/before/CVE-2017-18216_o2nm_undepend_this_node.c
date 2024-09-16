void o2nm_undepend_this_node(void)
{
	struct o2nm_node *local_node;

	local_node = o2nm_get_node_by_num(o2nm_this_node());
	BUG_ON(!local_node);

	o2nm_undepend_item(&local_node->nd_item);
	o2nm_node_put(local_node);
}
