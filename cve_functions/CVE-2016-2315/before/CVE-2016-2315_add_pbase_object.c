static void add_pbase_object(struct tree_desc *tree,
			     const char *name,
			     int cmplen,
			     const char *fullname)
{
	struct name_entry entry;
	int cmp;

	while (tree_entry(tree,&entry)) {
		if (S_ISGITLINK(entry.mode))
			continue;
		cmp = tree_entry_len(&entry) != cmplen ? 1 :
		      memcmp(name, entry.path, cmplen);
		if (cmp > 0)
			continue;
		if (cmp < 0)
			return;
		if (name[cmplen] != '/') {
			add_object_entry(entry.sha1,
					 object_type(entry.mode),
					 fullname, 1);
			return;
		}
		if (S_ISDIR(entry.mode)) {
			struct tree_desc sub;
			struct pbase_tree_cache *tree;
			const char *down = name+cmplen+1;
			int downlen = name_cmp_len(down);

			tree = pbase_tree_get(entry.sha1);
			if (!tree)
				return;
			init_tree_desc(&sub, tree->tree_data, tree->tree_size);

			add_pbase_object(&sub, down, downlen, fullname);
			pbase_tree_put(tree);
		}
	}
}
