encode_putfh(struct xdr_stream *xdr, const struct nfs_fh *fh, struct compound_hdr *hdr)
{
	int len = fh->size;
	__be32 *p;

	p = reserve_space(xdr, 8 + len);
	*p++ = cpu_to_be32(OP_PUTFH);
	xdr_encode_opaque(p, fh->data, len);
	hdr->nops++;
	hdr->replen += decode_putfh_maxsz;
}
