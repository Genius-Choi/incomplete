int main(int argc, char **argv)
{
	blkid_cache cache = NULL;
	int ret;

	blkid_init_debug(BLKID_DEBUG_ALL);
	if (argc > 2) {
		fprintf(stderr, "Usage: %s [filename]\n"
			"Test loading/saving a cache (filename)\n", argv[0]);
		exit(1);
	}

	if ((ret = blkid_get_cache(&cache, "/dev/null")) != 0) {
		fprintf(stderr, "%s: error creating cache (%d)\n",
			argv[0], ret);
		exit(1);
	}
	if ((ret = blkid_probe_all(cache)) < 0) {
		fprintf(stderr, "error (%d) probing devices\n", ret);
		exit(1);
	}
	cache->bic_filename = strdup(argv[1]);

	if ((ret = blkid_flush_cache(cache)) < 0) {
		fprintf(stderr, "error (%d) saving cache\n", ret);
		exit(1);
	}

	blkid_put_cache(cache);

	return ret;
}
