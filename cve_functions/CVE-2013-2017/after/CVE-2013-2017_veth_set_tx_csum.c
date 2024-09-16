static int veth_set_tx_csum(struct net_device *dev, u32 data)
{
	if (data)
		dev->features |= NETIF_F_NO_CSUM;
	else
		dev->features &= ~NETIF_F_NO_CSUM;
	return 0;
}
