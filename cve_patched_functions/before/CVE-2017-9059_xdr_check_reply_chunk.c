static __be32 *xdr_check_reply_chunk(__be32 *p, __be32 *end)
{
	__be32 *next;

	if (*p++ != xdr_zero) {
		next = p + 1 + be32_to_cpup(p) * rpcrdma_segment_maxsz;
		if (next > end)
			return NULL;
		p = next;
	}
	return p;
}
