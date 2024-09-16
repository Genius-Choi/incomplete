static void encode_setclientid_confirm(struct xdr_stream *xdr, const struct nfs4_setclientid_res *arg, struct compound_hdr *hdr)
{
	__be32 *p;

	p = reserve_space(xdr, 12 + NFS4_VERIFIER_SIZE);
	*p++ = cpu_to_be32(OP_SETCLIENTID_CONFIRM);
	p = xdr_encode_hyper(p, arg->clientid);
	xdr_encode_opaque_fixed(p, arg->confirm.data, NFS4_VERIFIER_SIZE);
	hdr->nops++;
	hdr->replen += decode_setclientid_confirm_maxsz;
}
