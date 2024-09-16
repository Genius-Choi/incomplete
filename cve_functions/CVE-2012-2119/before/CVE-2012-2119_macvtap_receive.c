static int macvtap_receive(struct sk_buff *skb)
{
	skb_push(skb, ETH_HLEN);
	return macvtap_forward(skb->dev, skb);
}
