buffer_apprentice(struct magic_set *ms, struct magic **bufs,
    size_t *sizes, size_t nbufs)
{
	size_t i, j;
	struct mlist *ml;
	struct magic_map *map;

	if (nbufs == 0)
		return -1;

	if (ms->mlist[0] != NULL)
		file_reset(ms);

	init_file_tables();

	for (i = 0; i < MAGIC_SETS; i++) {
		mlist_free(ms->mlist[i]);
		if ((ms->mlist[i] = mlist_alloc()) == NULL) {
			file_oomem(ms, sizeof(*ms->mlist[i]));
			goto fail;
		}
	}

	for (i = 0; i < nbufs; i++) {
		map = apprentice_buf(ms, bufs[i], sizes[i]);
		if (map == NULL)
			goto fail;

		for (j = 0; j < MAGIC_SETS; j++) {
			if (add_mlist(ms->mlist[j], map, j) == -1) {
				file_oomem(ms, sizeof(*ml));
				goto fail;
			}
		}
	}

	return 0;
fail:
	for (i = 0; i < MAGIC_SETS; i++) {
		mlist_free(ms->mlist[i]);
		ms->mlist[i] = NULL;
	}
	return -1;
}
