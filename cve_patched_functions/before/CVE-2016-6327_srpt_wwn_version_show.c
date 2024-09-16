static ssize_t srpt_wwn_version_show(struct config_item *item, char *buf)
{
	return scnprintf(buf, PAGE_SIZE, "%s\n", DRV_VERSION);
}
