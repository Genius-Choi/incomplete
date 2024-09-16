static int parse_dev(blkid_cache cache, blkid_dev *dev, char **cp)
{
	char *start, *tmp, *end, *name;
	int ret;

	if ((ret = parse_start(cp)) <= 0)
		return ret;

	start = tmp = strchr(*cp, '>');
	if (!start) {
		DBG(READ, ul_debug("blkid: short line parsing dev: %s", *cp));
		return -BLKID_ERR_CACHE;
	}
	start = skip_over_blank(start + 1);
	end = skip_over_word(start);

	DBG(READ, ul_debug("device should be %*s",
			       (int)(end - start), start));

	if (**cp == '>')
		*cp = end;
	else
		(*cp)++;

	*tmp = '\0';

	if (!(tmp = strrchr(end, '<')) || parse_end(&tmp) < 0) {
		DBG(READ, ul_debug("blkid: missing </device> ending: %s", end));
	} else if (tmp)
		*tmp = '\0';

	if (end - start <= 1) {
		DBG(READ, ul_debug("blkid: empty device name: %s", *cp));
		return -BLKID_ERR_CACHE;
	}

	name = strndup(start, end - start);
	if (name == NULL)
		return -BLKID_ERR_MEM;

	DBG(READ, ul_debug("found dev %s", name));

	if (!(*dev = blkid_get_dev(cache, name, BLKID_DEV_CREATE))) {
		free(name);
		return -BLKID_ERR_MEM;
	}

	free(name);
	return 1;
}
