static void encode_access(struct xdr_stream *xdr, u32 access, struct compound_hdr *hdr)
{
	__be32 *p;

	p = reserve_space(xdr, 8);
	*p++ = cpu_to_be32(OP_ACCESS);
	*p = cpu_to_be32(access);
	hdr->nops++;
	hdr->replen += decode_access_maxsz;
}
