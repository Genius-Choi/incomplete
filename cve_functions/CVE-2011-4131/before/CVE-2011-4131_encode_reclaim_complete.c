static void encode_reclaim_complete(struct xdr_stream *xdr,
				    struct nfs41_reclaim_complete_args *args,
				    struct compound_hdr *hdr)
{
	__be32 *p;

	p = reserve_space(xdr, 8);
	*p++ = cpu_to_be32(OP_RECLAIM_COMPLETE);
	*p++ = cpu_to_be32(args->one_fs);
	hdr->nops++;
	hdr->replen += decode_reclaim_complete_maxsz;
}
