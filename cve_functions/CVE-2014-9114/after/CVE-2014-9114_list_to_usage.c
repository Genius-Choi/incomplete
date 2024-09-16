static int list_to_usage(const char *list, int *flag)
{
	int mask = 0;
	const char *word = NULL, *p = list;

	if (p && strncmp(p, "no", 2) == 0) {
		*flag = BLKID_FLTR_NOTIN;
		p += 2;
	}
	if (!p || !*p)
		goto err;
	while(p) {
		word = p;
		p = strchr(p, ',');
		if (p)
			p++;
		if (!strncmp(word, "filesystem", 10))
			mask |= BLKID_USAGE_FILESYSTEM;
		else if (!strncmp(word, "raid", 4))
			mask |= BLKID_USAGE_RAID;
		else if (!strncmp(word, "crypto", 6))
			mask |= BLKID_USAGE_CRYPTO;
		else if (!strncmp(word, "other", 5))
			mask |= BLKID_USAGE_OTHER;
		else
			goto err;
	}
	return mask;
err:
	*flag = 0;
	fprintf(stderr, "unknown keyword in -u <list> argument: '%s'\n",
			word ? word : list);
	exit(BLKID_EXIT_OTHER);
}
