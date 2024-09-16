static int parse_end(char **cp)
{
	*cp = skip_over_blank(*cp);

	if (!strncmp(*cp, "</device>", 9)) {
		DBG(READ, ul_debug("found device trailer %9s", *cp));
		*cp += 9;
		return 0;
	}

	return -BLKID_ERR_CACHE;
}
