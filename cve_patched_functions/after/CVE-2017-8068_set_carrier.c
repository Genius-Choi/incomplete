static void set_carrier(struct net_device *net)
{
	pegasus_t *pegasus = netdev_priv(net);
	u16 tmp;

	if (read_mii_word(pegasus, pegasus->phy, MII_BMSR, &tmp))
		return;

	if (tmp & BMSR_LSTATUS)
		netif_carrier_on(net);
	else
		netif_carrier_off(net);
}
