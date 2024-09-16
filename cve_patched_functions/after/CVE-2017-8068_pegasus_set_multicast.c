static void pegasus_set_multicast(struct net_device *net)
{
	pegasus_t *pegasus = netdev_priv(net);

	if (net->flags & IFF_PROMISC) {
		pegasus->eth_regs[EthCtrl2] |= RX_PROMISCUOUS;
		netif_info(pegasus, link, net, "Promiscuous mode enabled\n");
	} else if (!netdev_mc_empty(net) || (net->flags & IFF_ALLMULTI)) {
		pegasus->eth_regs[EthCtrl0] |= RX_MULTICAST;
		pegasus->eth_regs[EthCtrl2] &= ~RX_PROMISCUOUS;
		netif_dbg(pegasus, link, net, "set allmulti\n");
	} else {
		pegasus->eth_regs[EthCtrl0] &= ~RX_MULTICAST;
		pegasus->eth_regs[EthCtrl2] &= ~RX_PROMISCUOUS;
	}
	update_eth_regs_async(pegasus);
}
