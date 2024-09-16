static bool bond_addr_in_mc_list(unsigned char *addr,
				 struct netdev_hw_addr_list *list,
				 int addrlen)
{
	struct netdev_hw_addr *ha;

	netdev_hw_addr_list_for_each(ha, list)
		if (!memcmp(ha->addr, addr, addrlen))
			return true;

	return false;
}
