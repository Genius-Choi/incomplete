static int inet_fill_ifaddr(struct sk_buff *skb, struct in_ifaddr *ifa,
			    u32 portid, u32 seq, int event, unsigned int flags)
{
	struct ifaddrmsg *ifm;
	struct nlmsghdr  *nlh;
	u32 preferred, valid;

	nlh = nlmsg_put(skb, portid, seq, event, sizeof(*ifm), flags);
	if (!nlh)
		return -EMSGSIZE;

	ifm = nlmsg_data(nlh);
	ifm->ifa_family = AF_INET;
	ifm->ifa_prefixlen = ifa->ifa_prefixlen;
	ifm->ifa_flags = ifa->ifa_flags;
	ifm->ifa_scope = ifa->ifa_scope;
	ifm->ifa_index = ifa->ifa_dev->dev->ifindex;

	if (!(ifm->ifa_flags & IFA_F_PERMANENT)) {
		preferred = ifa->ifa_preferred_lft;
		valid = ifa->ifa_valid_lft;
		if (preferred != INFINITY_LIFE_TIME) {
			long tval = (jiffies - ifa->ifa_tstamp) / HZ;

			if (preferred > tval)
				preferred -= tval;
			else
				preferred = 0;
			if (valid != INFINITY_LIFE_TIME) {
				if (valid > tval)
					valid -= tval;
				else
					valid = 0;
			}
		}
	} else {
		preferred = INFINITY_LIFE_TIME;
		valid = INFINITY_LIFE_TIME;
	}
	if ((ifa->ifa_address &&
	     nla_put_in_addr(skb, IFA_ADDRESS, ifa->ifa_address)) ||
	    (ifa->ifa_local &&
	     nla_put_in_addr(skb, IFA_LOCAL, ifa->ifa_local)) ||
	    (ifa->ifa_broadcast &&
	     nla_put_in_addr(skb, IFA_BROADCAST, ifa->ifa_broadcast)) ||
	    (ifa->ifa_label[0] &&
	     nla_put_string(skb, IFA_LABEL, ifa->ifa_label)) ||
	    nla_put_u32(skb, IFA_FLAGS, ifa->ifa_flags) ||
	    put_cacheinfo(skb, ifa->ifa_cstamp, ifa->ifa_tstamp,
			  preferred, valid))
		goto nla_put_failure;

	nlmsg_end(skb, nlh);
	return 0;

nla_put_failure:
	nlmsg_cancel(skb, nlh);
	return -EMSGSIZE;
}
