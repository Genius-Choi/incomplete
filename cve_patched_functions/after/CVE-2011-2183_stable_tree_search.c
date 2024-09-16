static struct page *stable_tree_search(struct page *page)
{
	struct rb_node *node = root_stable_tree.rb_node;
	struct stable_node *stable_node;

	stable_node = page_stable_node(page);
	if (stable_node) {			/* ksm page forked */
		get_page(page);
		return page;
	}

	while (node) {
		struct page *tree_page;
		int ret;

		cond_resched();
		stable_node = rb_entry(node, struct stable_node, node);
		tree_page = get_ksm_page(stable_node);
		if (!tree_page)
			return NULL;

		ret = memcmp_pages(page, tree_page);

		if (ret < 0) {
			put_page(tree_page);
			node = node->rb_left;
		} else if (ret > 0) {
			put_page(tree_page);
			node = node->rb_right;
		} else
			return tree_page;
	}

	return NULL;
}
