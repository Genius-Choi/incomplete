static void encode_renew(struct xdr_stream *xdr, const struct nfs_client *client_stateid, struct compound_hdr *hdr)
{
	__be32 *p;

	p = reserve_space(xdr, 12);
	*p++ = cpu_to_be32(OP_RENEW);
	xdr_encode_hyper(p, client_stateid->cl_clientid);
	hdr->nops++;
	hdr->replen += decode_renew_maxsz;
}
