find_clp_in_name_tree(struct xdr_netobj *name, struct rb_root *root)
{
	int cmp;
	struct rb_node *node = root->rb_node;
	struct nfs4_client *clp;

	while (node) {
		clp = rb_entry(node, struct nfs4_client, cl_namenode);
		cmp = compare_blob(&clp->cl_name, name);
		if (cmp > 0)
			node = node->rb_left;
		else if (cmp < 0)
			node = node->rb_right;
		else
			return clp;
	}
	return NULL;
}
