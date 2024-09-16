static ssize_t srpt_tpg_enable_store(struct config_item *item,
		const char *page, size_t count)
{
	struct se_portal_group *se_tpg = to_tpg(item);
	struct srpt_port *sport = container_of(se_tpg, struct srpt_port, port_tpg_1);
	unsigned long tmp;
        int ret;

	ret = kstrtoul(page, 0, &tmp);
	if (ret < 0) {
		pr_err("Unable to extract srpt_tpg_store_enable\n");
		return -EINVAL;
	}

	if ((tmp != 0) && (tmp != 1)) {
		pr_err("Illegal value for srpt_tpg_store_enable: %lu\n", tmp);
		return -EINVAL;
	}
	if (tmp == 1)
		sport->enabled = true;
	else
		sport->enabled = false;

	return count;
}
