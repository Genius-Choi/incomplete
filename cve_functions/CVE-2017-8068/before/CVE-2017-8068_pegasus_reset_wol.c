static inline void pegasus_reset_wol(struct net_device *dev)
{
	struct ethtool_wolinfo wol;

	memset(&wol, 0, sizeof wol);
	(void) pegasus_set_wol(dev, &wol);
}
