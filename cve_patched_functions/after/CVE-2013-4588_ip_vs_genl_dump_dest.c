static int ip_vs_genl_dump_dest(struct sk_buff *skb, struct ip_vs_dest *dest,
				struct netlink_callback *cb)
{
	void *hdr;

	hdr = genlmsg_put(skb, NETLINK_CB(cb->skb).pid, cb->nlh->nlmsg_seq,
			  &ip_vs_genl_family, NLM_F_MULTI,
			  IPVS_CMD_NEW_DEST);
	if (!hdr)
		return -EMSGSIZE;

	if (ip_vs_genl_fill_dest(skb, dest) < 0)
		goto nla_put_failure;

	return genlmsg_end(skb, hdr);

nla_put_failure:
	genlmsg_cancel(skb, hdr);
	return -EMSGSIZE;
}
