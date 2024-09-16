static int decode_readdir(struct xdr_stream *xdr, struct rpc_rqst *req, struct nfs4_readdir_res *readdir)
{
	struct xdr_buf	*rcvbuf = &req->rq_rcv_buf;
	struct kvec	*iov = rcvbuf->head;
	size_t		hdrlen;
	u32		recvd, pglen = rcvbuf->page_len;
	int		status;

	status = decode_op_hdr(xdr, OP_READDIR);
	if (!status)
		status = decode_verifier(xdr, readdir->verifier.data);
	if (unlikely(status))
		return status;
	dprintk("%s: verifier = %08x:%08x\n",
			__func__,
			((u32 *)readdir->verifier.data)[0],
			((u32 *)readdir->verifier.data)[1]);


	hdrlen = (char *) xdr->p - (char *) iov->iov_base;
	recvd = rcvbuf->len - hdrlen;
	if (pglen > recvd)
		pglen = recvd;
	xdr_read_pages(xdr, pglen);


	return pglen;
}
