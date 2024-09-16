static void encode_getfh(struct xdr_stream *xdr, struct compound_hdr *hdr)
{
	__be32 *p;

	p = reserve_space(xdr, 4);
	*p = cpu_to_be32(OP_GETFH);
	hdr->nops++;
	hdr->replen += decode_getfh_maxsz;
}
