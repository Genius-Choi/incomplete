static void encode_secinfo(struct xdr_stream *xdr, const struct qstr *name, struct compound_hdr *hdr)
{
	int len = name->len;
	__be32 *p;

	p = reserve_space(xdr, 8 + len);
	*p++ = cpu_to_be32(OP_SECINFO);
	xdr_encode_opaque(p, name->name, len);
	hdr->nops++;
	hdr->replen += decode_secinfo_maxsz;
}
