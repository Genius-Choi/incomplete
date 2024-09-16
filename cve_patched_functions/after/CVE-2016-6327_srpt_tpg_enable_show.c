static ssize_t srpt_tpg_enable_show(struct config_item *item, char *page)
{
	struct se_portal_group *se_tpg = to_tpg(item);
	struct srpt_port *sport = container_of(se_tpg, struct srpt_port, port_tpg_1);

	return snprintf(page, PAGE_SIZE, "%d\n", (sport->enabled) ? 1: 0);
}
