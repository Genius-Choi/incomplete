static struct o2nm_node *o2nm_node_ip_tree_lookup(struct o2nm_cluster *cluster,
						  __be32 ip_needle,
						  struct rb_node ***ret_p,
						  struct rb_node **ret_parent)
{
	struct rb_node **p = &cluster->cl_node_ip_tree.rb_node;
	struct rb_node *parent = NULL;
	struct o2nm_node *node, *ret = NULL;

	while (*p) {
		int cmp;

		parent = *p;
		node = rb_entry(parent, struct o2nm_node, nd_ip_node);

		cmp = memcmp(&ip_needle, &node->nd_ipv4_address,
				sizeof(ip_needle));
		if (cmp < 0)
			p = &(*p)->rb_left;
		else if (cmp > 0)
			p = &(*p)->rb_right;
		else {
			ret = node;
			break;
		}
	}

	if (ret_p != NULL)
		*ret_p = p;
	if (ret_parent != NULL)
		*ret_parent = parent;

	return ret;
}
