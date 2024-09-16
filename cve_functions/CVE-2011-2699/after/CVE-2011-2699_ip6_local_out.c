int ip6_local_out(struct sk_buff *skb)
{
	int err;

	err = __ip6_local_out(skb);
	if (likely(err == 1))
		err = dst_output(skb);

	return err;
}
