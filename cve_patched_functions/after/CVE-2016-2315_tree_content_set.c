static int tree_content_set(
	struct tree_entry *root,
	const char *p,
	const unsigned char *sha1,
	const uint16_t mode,
	struct tree_content *subtree)
{
	struct tree_content *t;
	const char *slash1;
	unsigned int i, n;
	struct tree_entry *e;

	slash1 = strchrnul(p, '/');
	n = slash1 - p;
	if (!n)
		die("Empty path component found in input");
	if (!*slash1 && !S_ISDIR(mode) && subtree)
		die("Non-directories cannot have subtrees");

	if (!root->tree)
		load_tree(root);
	t = root->tree;
	for (i = 0; i < t->entry_count; i++) {
		e = t->entries[i];
		if (e->name->str_len == n && !strncmp_icase(p, e->name->str_dat, n)) {
			if (!*slash1) {
				if (!S_ISDIR(mode)
						&& e->versions[1].mode == mode
						&& !hashcmp(e->versions[1].sha1, sha1))
					return 0;
				e->versions[1].mode = mode;
				hashcpy(e->versions[1].sha1, sha1);
				if (e->tree)
					release_tree_content_recursive(e->tree);
				e->tree = subtree;

				/*
				 * We need to leave e->versions[0].sha1 alone
				 * to avoid modifying the preimage tree used
				 * when writing out the parent directory.
				 * But after replacing the subdir with a
				 * completely different one, it's not a good
				 * delta base any more, and besides, we've
				 * thrown away the tree entries needed to
				 * make a delta against it.
				 *
				 * So let's just explicitly disable deltas
				 * for the subtree.
				 */
				if (S_ISDIR(e->versions[0].mode))
					e->versions[0].mode |= NO_DELTA;

				hashclr(root->versions[1].sha1);
				return 1;
			}
			if (!S_ISDIR(e->versions[1].mode)) {
				e->tree = new_tree_content(8);
				e->versions[1].mode = S_IFDIR;
			}
			if (!e->tree)
				load_tree(e);
			if (tree_content_set(e, slash1 + 1, sha1, mode, subtree)) {
				hashclr(root->versions[1].sha1);
				return 1;
			}
			return 0;
		}
	}

	if (t->entry_count == t->entry_capacity)
		root->tree = t = grow_tree_content(t, t->entry_count);
	e = new_tree_entry();
	e->name = to_atom(p, n);
	e->versions[0].mode = 0;
	hashclr(e->versions[0].sha1);
	t->entries[t->entry_count++] = e;
	if (*slash1) {
		e->tree = new_tree_content(8);
		e->versions[1].mode = S_IFDIR;
		tree_content_set(e, slash1 + 1, sha1, mode, subtree);
	} else {
		e->tree = subtree;
		e->versions[1].mode = mode;
		hashcpy(e->versions[1].sha1, sha1);
	}
	hashclr(root->versions[1].sha1);
	return 1;
}
