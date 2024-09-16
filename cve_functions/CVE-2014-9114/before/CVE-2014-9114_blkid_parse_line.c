static int blkid_parse_line(blkid_cache cache, blkid_dev *dev_p, char *cp)
{
	blkid_dev dev;
	int ret;

	if (!cache || !dev_p)
		return -BLKID_ERR_PARAM;

	*dev_p = NULL;

	DBG(READ, ul_debug("line: %s", cp));

	if ((ret = parse_dev(cache, dev_p, &cp)) <= 0)
		return ret;

	dev = *dev_p;

	while ((ret = parse_tag(cache, dev, &cp)) > 0) {
		;
	}

	if (dev->bid_type == NULL) {
		DBG(READ, ul_debug("blkid: device %s has no TYPE",dev->bid_name));
		blkid_free_dev(dev);
		goto done;
	}

	DBG(READ, blkid_debug_dump_dev(dev));

done:
	return ret;
}
