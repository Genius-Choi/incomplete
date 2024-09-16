static int l2tp_eth_dev_xmit(struct sk_buff *skb, struct net_device *dev)
{
	struct l2tp_eth *priv = netdev_priv(dev);
	struct l2tp_session *session = priv->session;

	l2tp_xmit_skb(session, skb, session->hdr_len);

	dev->stats.tx_bytes += skb->len;
	dev->stats.tx_packets++;

	return 0;
}
