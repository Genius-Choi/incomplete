static void encode_destroy_session(struct xdr_stream *xdr,
				   struct nfs4_session *session,
				   struct compound_hdr *hdr)
{
	__be32 *p;
	p = reserve_space(xdr, 4 + NFS4_MAX_SESSIONID_LEN);
	*p++ = cpu_to_be32(OP_DESTROY_SESSION);
	xdr_encode_opaque_fixed(p, session->sess_id.data, NFS4_MAX_SESSIONID_LEN);
	hdr->nops++;
	hdr->replen += decode_destroy_session_maxsz;
}
