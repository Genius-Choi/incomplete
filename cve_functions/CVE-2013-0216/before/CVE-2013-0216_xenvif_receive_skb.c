void xenvif_receive_skb(struct xenvif *vif, struct sk_buff *skb)
{
	netif_rx_ni(skb);
}
