static ssize_t rd_set_configfs_dev_params(struct se_device *dev,
		const char *page, ssize_t count)
{
	struct rd_dev *rd_dev = RD_DEV(dev);
	char *orig, *ptr, *opts;
	substring_t args[MAX_OPT_ARGS];
	int ret = 0, arg, token;

	opts = kstrdup(page, GFP_KERNEL);
	if (!opts)
		return -ENOMEM;

	orig = opts;

	while ((ptr = strsep(&opts, ",\n")) != NULL) {
		if (!*ptr)
			continue;

		token = match_token(ptr, tokens, args);
		switch (token) {
		case Opt_rd_pages:
			match_int(args, &arg);
			rd_dev->rd_page_count = arg;
			pr_debug("RAMDISK: Referencing Page"
				" Count: %u\n", rd_dev->rd_page_count);
			rd_dev->rd_flags |= RDF_HAS_PAGE_COUNT;
			break;
		case Opt_rd_nullio:
			match_int(args, &arg);
			if (arg != 1)
				break;

			pr_debug("RAMDISK: Setting NULLIO flag: %d\n", arg);
			rd_dev->rd_flags |= RDF_NULLIO;
			break;
		default:
			break;
		}
	}

	kfree(orig);
	return (!ret) ? count : ret;
}
