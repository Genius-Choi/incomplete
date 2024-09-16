static void add_cache_tree(struct cache_tree *it, struct rev_info *revs,
			   struct strbuf *path)
{
	size_t baselen = path->len;
	int i;

	if (it->entry_count >= 0) {
		struct tree *tree = lookup_tree(it->sha1);
		add_pending_object_with_path(revs, &tree->object, "",
					     040000, path->buf);
	}

	for (i = 0; i < it->subtree_nr; i++) {
		struct cache_tree_sub *sub = it->down[i];
		strbuf_addf(path, "%s%s", baselen ? "/" : "", sub->name);
		add_cache_tree(sub->cache_tree, revs, path);
		strbuf_setlen(path, baselen);
	}

}
