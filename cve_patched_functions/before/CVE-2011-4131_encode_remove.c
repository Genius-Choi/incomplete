static void encode_remove(struct xdr_stream *xdr, const struct qstr *name, struct compound_hdr *hdr)
{
	__be32 *p;

	p = reserve_space(xdr, 8 + name->len);
	*p++ = cpu_to_be32(OP_REMOVE);
	xdr_encode_opaque(p, name->name, name->len);
	hdr->nops++;
	hdr->replen += decode_remove_maxsz;
}
