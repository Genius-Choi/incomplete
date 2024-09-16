static void pegasus_set_msglevel(struct net_device *dev, u32 v)
{
	pegasus_t *pegasus = netdev_priv(dev);
	pegasus->msg_enable = v;
}
