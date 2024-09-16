static int ip6_finish_output(struct sk_buff *skb)
{
	if ((skb->len > ip6_skb_dst_mtu(skb) && !skb_is_gso(skb)) ||
	    dst_allfrag(skb_dst(skb)))
		return ip6_fragment(skb, ip6_finish_output2);
	else
		return ip6_finish_output2(skb);
}
