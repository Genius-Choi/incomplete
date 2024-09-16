static int nfs4_xdr_dec_pathconf(struct rpc_rqst *req, __be32 *p, struct nfs_pathconf *pathconf)
{
	struct xdr_stream xdr;
	struct compound_hdr hdr;
	int status;

	xdr_init_decode(&xdr, &req->rq_rcv_buf, p);
	status = decode_compound_hdr(&xdr, &hdr);
	if (!status)
		status = decode_putfh(&xdr);
	if (!status)
		status = decode_pathconf(&xdr, pathconf);
	return status;
}
