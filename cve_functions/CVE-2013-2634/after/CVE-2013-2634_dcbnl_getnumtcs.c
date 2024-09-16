static int dcbnl_getnumtcs(struct net_device *netdev, struct nlmsghdr *nlh,
			   u32 seq, struct nlattr **tb, struct sk_buff *skb)
{
	struct nlattr *data[DCB_NUMTCS_ATTR_MAX + 1], *nest;
	u8 value;
	int ret;
	int i;
	int getall = 0;

	if (!tb[DCB_ATTR_NUMTCS])
		return -EINVAL;

	if (!netdev->dcbnl_ops->getnumtcs)
		return -EOPNOTSUPP;

	ret = nla_parse_nested(data, DCB_NUMTCS_ATTR_MAX, tb[DCB_ATTR_NUMTCS],
	                       dcbnl_numtcs_nest);
	if (ret)
		return ret;

	nest = nla_nest_start(skb, DCB_ATTR_NUMTCS);
	if (!nest)
		return -EMSGSIZE;

	if (data[DCB_NUMTCS_ATTR_ALL])
		getall = 1;

	for (i = DCB_NUMTCS_ATTR_ALL+1; i <= DCB_NUMTCS_ATTR_MAX; i++) {
		if (!getall && !data[i])
			continue;

		ret = netdev->dcbnl_ops->getnumtcs(netdev, i, &value);
		if (!ret) {
			ret = nla_put_u8(skb, i, value);
			if (ret) {
				nla_nest_cancel(skb, nest);
				return ret;
			}
		} else
			return -EINVAL;
	}
	nla_nest_end(skb, nest);

	return 0;
}
