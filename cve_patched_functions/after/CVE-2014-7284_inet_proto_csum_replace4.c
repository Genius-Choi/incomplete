void inet_proto_csum_replace4(__sum16 *sum, struct sk_buff *skb,
			      __be32 from, __be32 to, int pseudohdr)
{
	__be32 diff[] = { ~from, to };
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
