static struct rb_entry *__lookup_rb_tree_slow(struct rb_root *root,
							unsigned int ofs)
{
	struct rb_node *node = root->rb_node;
	struct rb_entry *re;

	while (node) {
		re = rb_entry(node, struct rb_entry, rb_node);

		if (ofs < re->ofs)
			node = node->rb_left;
		else if (ofs >= re->ofs + re->len)
			node = node->rb_right;
		else
			return re;
	}
	return NULL;
}
