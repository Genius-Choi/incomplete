static void cleanup_preferred_base(void)
{
	struct pbase_tree *it;
	unsigned i;

	it = pbase_tree;
	pbase_tree = NULL;
	while (it) {
		struct pbase_tree *this = it;
		it = this->next;
		free(this->pcache.tree_data);
		free(this);
	}

	for (i = 0; i < ARRAY_SIZE(pbase_tree_cache); i++) {
		if (!pbase_tree_cache[i])
			continue;
		free(pbase_tree_cache[i]->tree_data);
		free(pbase_tree_cache[i]);
		pbase_tree_cache[i] = NULL;
	}

	free(done_pbase_paths);
	done_pbase_paths = NULL;
	done_pbase_paths_num = done_pbase_paths_alloc = 0;
}
