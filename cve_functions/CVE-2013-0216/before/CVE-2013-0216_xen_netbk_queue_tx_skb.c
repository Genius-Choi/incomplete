void xen_netbk_queue_tx_skb(struct xenvif *vif, struct sk_buff *skb)
{
	struct xen_netbk *netbk = vif->netbk;

	skb_queue_tail(&netbk->rx_queue, skb);

	xen_netbk_kick_thread(netbk);
}
