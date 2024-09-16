static int rtl8150_ioctl(struct net_device *netdev, struct ifreq *rq, int cmd)
{
	rtl8150_t *dev = netdev_priv(netdev);
	u16 *data = (u16 *) & rq->ifr_ifru;
	int res = 0;

	switch (cmd) {
	case SIOCDEVPRIVATE:
		data[0] = dev->phy;
	case SIOCDEVPRIVATE + 1:
		read_mii_word(dev, dev->phy, (data[1] & 0x1f), &data[3]);
		break;
	case SIOCDEVPRIVATE + 2:
		if (!capable(CAP_NET_ADMIN))
			return -EPERM;
		write_mii_word(dev, dev->phy, (data[1] & 0x1f), data[2]);
		break;
	default:
		res = -EOPNOTSUPP;
	}

	return res;
}
