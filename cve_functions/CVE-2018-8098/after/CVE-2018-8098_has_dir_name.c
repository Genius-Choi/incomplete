static int has_dir_name(git_index *index,
		const git_index_entry *entry, int ok_to_replace)
{
	int retval = 0;
	int stage = GIT_IDXENTRY_STAGE(entry);
	const char *name = entry->path;
	const char *slash = name + strlen(name);

	for (;;) {
		size_t len, pos;

		for (;;) {
			if (*--slash == '/')
				break;
			if (slash <= entry->path)
				return retval;
		}
		len = slash - name;

		if (!index_find(&pos, index, name, len, stage)) {
			retval = -1;
			if (!ok_to_replace)
				break;

			if (index_remove_entry(index, pos) < 0)
				break;
			continue;
		}

		/*
		 * Trivial optimization: if we find an entry that
		 * already matches the sub-directory, then we know
		 * we're ok, and we can exit.
		 */
		for (; pos < index->entries.length; ++pos) {
			struct entry_internal *p = index->entries.contents[pos];

			if (p->pathlen <= len ||
			    p->path[len] != '/' ||
			    memcmp(p->path, name, len))
				break; /* not our subdirectory */

			if (GIT_IDXENTRY_STAGE(&p->entry) == stage)
				return retval;
		}
	}

	return retval;
}
