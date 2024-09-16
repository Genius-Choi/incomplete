static void set_carrier(struct net_device *netdev)
{
	rtl8150_t *dev = netdev_priv(netdev);
	short tmp;

	get_registers(dev, CSCR, 2, &tmp);
	if (tmp & CSCR_LINK_STATUS)
		netif_carrier_on(netdev);
	else
		netif_carrier_off(netdev);
}
