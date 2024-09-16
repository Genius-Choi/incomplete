static void encode_rename(struct xdr_stream *xdr, const struct qstr *oldname, const struct qstr *newname, struct compound_hdr *hdr)
{
	__be32 *p;

	p = reserve_space(xdr, 4);
	*p = cpu_to_be32(OP_RENAME);
	encode_string(xdr, oldname->len, oldname->name);
	encode_string(xdr, newname->len, newname->name);
	hdr->nops++;
	hdr->replen += decode_rename_maxsz;
}
