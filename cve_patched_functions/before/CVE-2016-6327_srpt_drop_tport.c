static void srpt_drop_tport(struct se_wwn *wwn)
{
	struct srpt_port *sport = container_of(wwn, struct srpt_port, port_wwn);

	pr_debug("drop_tport(%s\n", config_item_name(&sport->port_wwn.wwn_group.cg_item));
}
