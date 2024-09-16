static int mdio_read(struct net_device *dev, int phy_id, int loc)
{
	pegasus_t *pegasus = netdev_priv(dev);
	u16 res;

	read_mii_word(pegasus, phy_id, loc, &res);
	return (int)res;
}
