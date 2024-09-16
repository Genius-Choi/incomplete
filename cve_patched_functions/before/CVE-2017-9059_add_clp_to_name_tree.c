add_clp_to_name_tree(struct nfs4_client *new_clp, struct rb_root *root)
{
	struct rb_node **new = &(root->rb_node), *parent = NULL;
	struct nfs4_client *clp;

	while (*new) {
		clp = rb_entry(*new, struct nfs4_client, cl_namenode);
		parent = *new;

		if (compare_blob(&clp->cl_name, &new_clp->cl_name) > 0)
			new = &((*new)->rb_left);
		else
			new = &((*new)->rb_right);
	}

	rb_link_node(&new_clp->cl_namenode, parent, new);
	rb_insert_color(&new_clp->cl_namenode, root);
}
