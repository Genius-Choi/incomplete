static void encode_delegreturn(struct xdr_stream *xdr, const nfs4_stateid *stateid, struct compound_hdr *hdr)
{
	__be32 *p;

	p = reserve_space(xdr, 4+NFS4_STATEID_SIZE);

	*p++ = cpu_to_be32(OP_DELEGRETURN);
	xdr_encode_opaque_fixed(p, stateid->data, NFS4_STATEID_SIZE);
	hdr->nops++;
	hdr->replen += decode_delegreturn_maxsz;
}
