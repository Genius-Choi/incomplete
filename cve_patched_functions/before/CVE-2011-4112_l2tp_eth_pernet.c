static inline struct l2tp_eth_net *l2tp_eth_pernet(struct net *net)
{
	return net_generic(net, l2tp_eth_net_id);
}
