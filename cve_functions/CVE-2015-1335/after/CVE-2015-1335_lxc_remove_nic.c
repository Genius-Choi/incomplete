static void lxc_remove_nic(struct lxc_list *it)
{
	struct lxc_netdev *netdev = it->elem;
	struct lxc_list *it2,*next;

	lxc_list_del(it);

	free(netdev->link);
	free(netdev->name);
	if (netdev->type == LXC_NET_VETH)
		free(netdev->priv.veth_attr.pair);
	free(netdev->upscript);
	free(netdev->hwaddr);
	free(netdev->mtu);
	free(netdev->ipv4_gateway);
	free(netdev->ipv6_gateway);
	lxc_list_for_each_safe(it2, &netdev->ipv4, next) {
		lxc_list_del(it2);
		free(it2->elem);
		free(it2);
	}
	lxc_list_for_each_safe(it2, &netdev->ipv6, next) {
		lxc_list_del(it2);
		free(it2->elem);
		free(it2);
	}
	free(netdev);
	free(it);
}
