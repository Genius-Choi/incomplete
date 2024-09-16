static u32 veth_get_tx_csum(struct net_device *dev)
{
	return (dev->features & NETIF_F_NO_CSUM) != 0;
}
