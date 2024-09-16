static struct sk_buff *dcbnl_newmsg(int type, u8 cmd, u32 port, u32 seq,
				    u32 flags, struct nlmsghdr **nlhp)
{
	struct sk_buff *skb;
	struct dcbmsg *dcb;
	struct nlmsghdr *nlh;

	skb = nlmsg_new(NLMSG_DEFAULT_SIZE, GFP_KERNEL);
	if (!skb)
		return NULL;

	nlh = nlmsg_put(skb, port, seq, type, sizeof(*dcb), flags);
	BUG_ON(!nlh);

	dcb = nlmsg_data(nlh);
	dcb->dcb_family = AF_UNSPEC;
	dcb->cmd = cmd;
	dcb->dcb_pad = 0;

	if (nlhp)
		*nlhp = nlh;

	return skb;
}
