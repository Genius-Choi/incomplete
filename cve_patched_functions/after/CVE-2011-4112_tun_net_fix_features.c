static u32 tun_net_fix_features(struct net_device *dev, u32 features)
{
	struct tun_struct *tun = netdev_priv(dev);

	return (features & tun->set_features) | (features & ~TUN_USER_FEATURES);
}
