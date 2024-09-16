static int dcbnl_ieee_del(struct net_device *netdev, struct nlmsghdr *nlh,
			  u32 seq, struct nlattr **tb, struct sk_buff *skb)
{
	const struct dcbnl_rtnl_ops *ops = netdev->dcbnl_ops;
	struct nlattr *ieee[DCB_ATTR_IEEE_MAX + 1];
	int err;

	if (!ops)
		return -EOPNOTSUPP;

	if (!tb[DCB_ATTR_IEEE])
		return -EINVAL;

	err = nla_parse_nested(ieee, DCB_ATTR_IEEE_MAX,
			       tb[DCB_ATTR_IEEE], dcbnl_ieee_policy);
	if (err)
		return err;

	if (ieee[DCB_ATTR_IEEE_APP_TABLE]) {
		struct nlattr *attr;
		int rem;

		nla_for_each_nested(attr, ieee[DCB_ATTR_IEEE_APP_TABLE], rem) {
			struct dcb_app *app_data;

			if (nla_type(attr) != DCB_ATTR_IEEE_APP)
				continue;
			app_data = nla_data(attr);
			if (ops->ieee_delapp)
				err = ops->ieee_delapp(netdev, app_data);
			else
				err = dcb_ieee_delapp(netdev, app_data);
			if (err)
				goto err;
		}
	}

err:
	err = nla_put_u8(skb, DCB_ATTR_IEEE, err);
	dcbnl_ieee_notify(netdev, RTM_SETDCB, DCB_CMD_IEEE_DEL, seq, 0);
	return err;
}
