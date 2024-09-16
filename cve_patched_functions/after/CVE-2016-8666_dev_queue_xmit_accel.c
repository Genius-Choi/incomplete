int dev_queue_xmit_accel(struct sk_buff *skb, void *accel_priv)
{
	return __dev_queue_xmit(skb, accel_priv);
}
