static int get_vlan(struct genl_info *info,
		    struct cfg80211_registered_device *rdev,
		    struct net_device **vlan)
{
	struct nlattr *vlanattr = info->attrs[NL80211_ATTR_STA_VLAN];
	*vlan = NULL;

	if (vlanattr) {
		*vlan = dev_get_by_index(genl_info_net(info),
					 nla_get_u32(vlanattr));
		if (!*vlan)
			return -ENODEV;
		if (!(*vlan)->ieee80211_ptr)
			return -EINVAL;
		if ((*vlan)->ieee80211_ptr->wiphy != &rdev->wiphy)
			return -EINVAL;
		if (!netif_running(*vlan))
			return -ENETDOWN;
	}
	return 0;
}
