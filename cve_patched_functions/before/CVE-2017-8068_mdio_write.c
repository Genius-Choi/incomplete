static void mdio_write(struct net_device *dev, int phy_id, int loc, int val)
{
	pegasus_t *pegasus = netdev_priv(dev);
	u16 data = val;

	write_mii_word(pegasus, phy_id, loc, &data);
}
