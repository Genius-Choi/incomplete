static u32 pegasus_get_msglevel(struct net_device *dev)
{
	pegasus_t *pegasus = netdev_priv(dev);
	return pegasus->msg_enable;
}
