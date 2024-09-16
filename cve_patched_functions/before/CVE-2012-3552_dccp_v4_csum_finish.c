static inline __sum16 dccp_v4_csum_finish(struct sk_buff *skb,
				      __be32 src, __be32 dst)
{
	return csum_tcpudp_magic(src, dst, skb->len, IPPROTO_DCCP, skb->csum);
}
