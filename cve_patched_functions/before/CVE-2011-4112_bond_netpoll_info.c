static struct netpoll_info *bond_netpoll_info(struct bonding *bond)
{
	return bond->dev->npinfo;
}
