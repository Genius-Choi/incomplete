static void pvc_setup(struct net_device *dev)
{
	dev->type = ARPHRD_DLCI;
	dev->flags = IFF_POINTOPOINT;
	dev->hard_header_len = 10;
	dev->addr_len = 2;
	dev->priv_flags &= ~IFF_XMIT_DST_RELEASE;
}
