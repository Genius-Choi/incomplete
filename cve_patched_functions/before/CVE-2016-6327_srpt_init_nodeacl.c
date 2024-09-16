static int srpt_init_nodeacl(struct se_node_acl *se_nacl, const char *name)
{
	u8 i_port_id[16];

	if (srpt_parse_i_port_id(i_port_id, name) < 0) {
		pr_err("invalid initiator port ID %s\n", name);
		return -EINVAL;
	}
	return 0;
}
