bool ipv6_opt_accepted(const struct sock *sk, const struct sk_buff *skb,
		       const struct inet6_skb_parm *opt)
{
	const struct ipv6_pinfo *np = inet6_sk(sk);

	if (np->rxopt.all) {
		if (((opt->flags & IP6SKB_HOPBYHOP) &&
		     (np->rxopt.bits.hopopts || np->rxopt.bits.ohopopts)) ||
		    (ip6_flowinfo((struct ipv6hdr *) skb_network_header(skb)) &&
		     np->rxopt.bits.rxflow) ||
		    (opt->srcrt && (np->rxopt.bits.srcrt ||
		     np->rxopt.bits.osrcrt)) ||
		    ((opt->dst1 || opt->dst0) &&
		     (np->rxopt.bits.dstopts || np->rxopt.bits.odstopts)))
			return true;
	}
	return false;
}
