uint32_t update_free(DOS_FS * fs)
{
    uint32_t i;
    uint32_t free = 0;
    int do_set = 0;

    for (i = 2; i < fs->clusters + 2; i++) {
	FAT_ENTRY curEntry;
	get_fat(&curEntry, fs->fat, i, fs);

	if (!get_owner(fs, i) && !FAT_IS_BAD(fs, curEntry.value))
	    ++free;
    }

    if (!fs->fsinfo_start)
	return free;

    if (verbose)
	printf("Checking free cluster summary.\n");
    if (fs->free_clusters != 0xFFFFFFFF) {
	if (free != fs->free_clusters) {
	    printf("Free cluster summary wrong (%ld vs. really %ld)\n",
		   (long)fs->free_clusters, (long)free);
	    if (interactive)
		printf("1) Correct\n2) Don't correct\n");
	    else
		printf("  Auto-correcting.\n");
	    if (!interactive || get_key("12", "?") == '1')
		do_set = 1;
	}
    } else {
	printf("Free cluster summary uninitialized (should be %ld)\n", (long)free);
	if (rw) {
	    if (interactive)
		printf("1) Set it\n2) Leave it uninitialized\n");
	    else
		printf("  Auto-setting.\n");
	    if (!interactive || get_key("12", "?") == '1')
		do_set = 1;
	}
    }

    if (do_set) {
	uint32_t le_free = htole32(free);
	fs->free_clusters = free;
	fs_write(fs->fsinfo_start + offsetof(struct info_sector, free_clusters),
		 sizeof(le_free), &le_free);
    }

    return free;
}
