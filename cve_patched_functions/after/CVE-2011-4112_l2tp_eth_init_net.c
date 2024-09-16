static __net_init int l2tp_eth_init_net(struct net *net)
{
	struct l2tp_eth_net *pn = net_generic(net, l2tp_eth_net_id);

	INIT_LIST_HEAD(&pn->l2tp_eth_dev_list);
	spin_lock_init(&pn->l2tp_eth_lock);

	return 0;
}
