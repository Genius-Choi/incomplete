void inet_proto_csum_replace16(__sum16 *sum, struct sk_buff *skb,
			       const __be32 *from, const __be32 *to,
			       int pseudohdr)
{
	__be32 diff[] = {
		~from[0], ~from[1], ~from[2], ~from[3],
		to[0], to[1], to[2], to[3],
	};
	if (skb->ip_summed != CHECKSUM_PARTIAL) {
		*sum = csum_fold(csum_partial(diff, sizeof(diff),
				 ~csum_unfold(*sum)));
		if (skb->ip_summed == CHECKSUM_COMPLETE && pseudohdr)
			skb->csum = ~csum_partial(diff, sizeof(diff),
						  ~skb->csum);
	} else if (pseudohdr)
		*sum = ~csum_fold(csum_partial(diff, sizeof(diff),
				  csum_unfold(*sum)));
}
