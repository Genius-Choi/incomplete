static void srpt_drop_tpg(struct se_portal_group *tpg)
{
	struct srpt_port *sport = container_of(tpg,
				struct srpt_port, port_tpg_1);

	sport->enabled = false;
	core_tpg_deregister(&sport->port_tpg_1);
}
