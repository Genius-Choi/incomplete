int fib_validate_source(struct sk_buff *skb, __be32 src, __be32 dst,
			u8 tos, int oif, struct net_device *dev,
			struct in_device *idev, u32 *itag)
{
	int r = secpath_exists(skb) ? 0 : IN_DEV_RPFILTER(idev);

	if (!r && !fib_num_tclassid_users(dev_net(dev)) &&
	    IN_DEV_ACCEPT_LOCAL(idev) &&
	    (dev->ifindex != oif || !IN_DEV_TX_REDIRECTS(idev))) {
		*itag = 0;
		return 0;
	}
	return __fib_validate_source(skb, src, dst, tos, oif, dev, r, idev, itag);
}
