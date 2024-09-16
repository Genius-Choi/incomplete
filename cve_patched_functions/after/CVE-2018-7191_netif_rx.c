int netif_rx(struct sk_buff *skb)
{
	trace_netif_rx_entry(skb);

	return netif_rx_internal(skb);
}
