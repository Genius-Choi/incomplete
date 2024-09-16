static char *srpt_get_fabric_wwn(struct se_portal_group *tpg)
{
	struct srpt_port *sport = container_of(tpg, struct srpt_port, port_tpg_1);

	return sport->port_guid;
}
