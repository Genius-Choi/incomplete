static int addrconf_ifid_ip6tnl(u8 *eui, struct net_device *dev)
{
	memcpy(eui, dev->perm_addr, 3);
	memcpy(eui + 5, dev->perm_addr + 3, 3);
	eui[3] = 0xFF;
	eui[4] = 0xFE;
	eui[0] ^= 2;
	return 0;
}
