static void add_preferred_base_object(const char *name)
{
	struct pbase_tree *it;
	int cmplen;
	unsigned hash = pack_name_hash(name);

	if (!num_preferred_base || check_pbase_path(hash))
		return;

	cmplen = name_cmp_len(name);
	for (it = pbase_tree; it; it = it->next) {
		if (cmplen == 0) {
			add_object_entry(it->pcache.sha1, OBJ_TREE, NULL, 1);
		}
		else {
			struct tree_desc tree;
			init_tree_desc(&tree, it->pcache.tree_data, it->pcache.tree_size);
			add_pbase_object(&tree, name, cmplen, name);
		}
	}
}
