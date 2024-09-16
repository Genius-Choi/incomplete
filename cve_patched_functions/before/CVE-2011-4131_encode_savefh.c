encode_savefh(struct xdr_stream *xdr, struct compound_hdr *hdr)
{
	__be32 *p;

	p = reserve_space(xdr, 4);
	*p = cpu_to_be32(OP_SAVEFH);
	hdr->nops++;
	hdr->replen += decode_savefh_maxsz;
}
