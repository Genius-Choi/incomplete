static int nfs4_xdr_dec_remove(struct rpc_rqst *rqstp, struct xdr_stream *xdr,
			       struct nfs_removeres *res)
{
	struct compound_hdr hdr;
	int status;

	status = decode_compound_hdr(xdr, &hdr);
	if (status)
		goto out;
	status = decode_sequence(xdr, &res->seq_res, rqstp);
	if (status)
		goto out;
	status = decode_putfh(xdr);
	if (status)
		goto out;
	status = decode_remove(xdr, &res->cinfo);
	if (status)
		goto out;
	decode_getfattr(xdr, res->dir_attr, res->server,
			!RPC_IS_ASYNC(rqstp->rq_task));
out:
	return status;
}
