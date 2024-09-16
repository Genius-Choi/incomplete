static int ip6mr_rule_fill(struct fib_rule *rule, struct sk_buff *skb,
			   struct fib_rule_hdr *frh)
{
	frh->dst_len = 0;
	frh->src_len = 0;
	frh->tos     = 0;
	return 0;
}
