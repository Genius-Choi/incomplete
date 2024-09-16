static int nlattr_to_dccp(struct nlattr *cda[], struct nf_conn *ct)
{
	struct nlattr *attr = cda[CTA_PROTOINFO_DCCP];
	struct nlattr *tb[CTA_PROTOINFO_DCCP_MAX + 1];
	int err;

	if (!attr)
		return 0;

	err = nla_parse_nested(tb, CTA_PROTOINFO_DCCP_MAX, attr,
			       dccp_nla_policy);
	if (err < 0)
		return err;

	if (!tb[CTA_PROTOINFO_DCCP_STATE] ||
	    !tb[CTA_PROTOINFO_DCCP_ROLE] ||
	    nla_get_u8(tb[CTA_PROTOINFO_DCCP_ROLE]) > CT_DCCP_ROLE_MAX ||
	    nla_get_u8(tb[CTA_PROTOINFO_DCCP_STATE]) >= CT_DCCP_IGNORE) {
		return -EINVAL;
	}

	spin_lock_bh(&ct->lock);
	ct->proto.dccp.state = nla_get_u8(tb[CTA_PROTOINFO_DCCP_STATE]);
	if (nla_get_u8(tb[CTA_PROTOINFO_DCCP_ROLE]) == CT_DCCP_ROLE_CLIENT) {
		ct->proto.dccp.role[IP_CT_DIR_ORIGINAL] = CT_DCCP_ROLE_CLIENT;
		ct->proto.dccp.role[IP_CT_DIR_REPLY] = CT_DCCP_ROLE_SERVER;
	} else {
		ct->proto.dccp.role[IP_CT_DIR_ORIGINAL] = CT_DCCP_ROLE_SERVER;
		ct->proto.dccp.role[IP_CT_DIR_REPLY] = CT_DCCP_ROLE_CLIENT;
	}
	if (tb[CTA_PROTOINFO_DCCP_HANDSHAKE_SEQ]) {
		ct->proto.dccp.handshake_seq =
		be64_to_cpu(nla_get_be64(tb[CTA_PROTOINFO_DCCP_HANDSHAKE_SEQ]));
	}
	spin_unlock_bh(&ct->lock);
	return 0;
}
