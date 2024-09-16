static ssize_t srpt_tpg_attrib_srp_max_rsp_size_show(struct config_item *item,
		char *page)
{
	struct se_portal_group *se_tpg = attrib_to_tpg(item);
	struct srpt_port *sport = container_of(se_tpg, struct srpt_port, port_tpg_1);

	return sprintf(page, "%u\n", sport->port_attrib.srp_max_rsp_size);
}
