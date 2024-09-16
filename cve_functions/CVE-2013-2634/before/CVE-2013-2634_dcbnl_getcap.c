static int dcbnl_getcap(struct net_device *netdev, struct nlmsghdr *nlh,
			u32 seq, struct nlattr **tb, struct sk_buff *skb)
{
	struct nlattr *data[DCB_CAP_ATTR_MAX + 1], *nest;
	u8 value;
	int ret;
	int i;
	int getall = 0;

	if (!tb[DCB_ATTR_CAP])
		return -EINVAL;

	if (!netdev->dcbnl_ops->getcap)
		return -EOPNOTSUPP;

	ret = nla_parse_nested(data, DCB_CAP_ATTR_MAX, tb[DCB_ATTR_CAP],
	                       dcbnl_cap_nest);
	if (ret)
		return ret;

	nest = nla_nest_start(skb, DCB_ATTR_CAP);
	if (!nest)
		return -EMSGSIZE;

	if (data[DCB_CAP_ATTR_ALL])
		getall = 1;

	for (i = DCB_CAP_ATTR_ALL+1; i <= DCB_CAP_ATTR_MAX; i++) {
		if (!getall && !data[i])
			continue;

		if (!netdev->dcbnl_ops->getcap(netdev, i, &value)) {
			ret = nla_put_u8(skb, i, value);
			if (ret) {
				nla_nest_cancel(skb, nest);
				return ret;
			}
		}
	}
	nla_nest_end(skb, nest);

	return 0;
}
