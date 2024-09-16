void add_index_objects_to_pending(struct rev_info *revs, unsigned flags)
{
	int i;

	read_cache();
	for (i = 0; i < active_nr; i++) {
		struct cache_entry *ce = active_cache[i];
		struct blob *blob;

		if (S_ISGITLINK(ce->ce_mode))
			continue;

		blob = lookup_blob(ce->sha1);
		if (!blob)
			die("unable to add index blob to traversal");
		add_pending_object_with_path(revs, &blob->object, "",
					     ce->ce_mode, ce->name);
	}

	if (active_cache_tree) {
		struct strbuf path = STRBUF_INIT;
		add_cache_tree(active_cache_tree, revs, &path);
		strbuf_release(&path);
	}
}
