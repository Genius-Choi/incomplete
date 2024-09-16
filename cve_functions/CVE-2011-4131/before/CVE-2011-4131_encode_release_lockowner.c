static void encode_release_lockowner(struct xdr_stream *xdr, const struct nfs_lowner *lowner, struct compound_hdr *hdr)
{
	__be32 *p;

	p = reserve_space(xdr, 4);
	*p = cpu_to_be32(OP_RELEASE_LOCKOWNER);
	encode_lockowner(xdr, lowner);
	hdr->nops++;
	hdr->replen += decode_release_lockowner_maxsz;
}
