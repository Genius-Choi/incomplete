static int macvtap_forward(struct net_device *dev, struct sk_buff *skb)
{
	struct macvtap_queue *q = macvtap_get_queue(dev, skb);
	if (!q)
		goto drop;

	if (skb_queue_len(&q->sk.sk_receive_queue) >= dev->tx_queue_len)
		goto drop;

	skb_queue_tail(&q->sk.sk_receive_queue, skb);
	wake_up_interruptible_poll(sk_sleep(&q->sk), POLLIN | POLLRDNORM | POLLRDBAND);
	return NET_RX_SUCCESS;

drop:
	kfree_skb(skb);
	return NET_RX_DROP;
}
