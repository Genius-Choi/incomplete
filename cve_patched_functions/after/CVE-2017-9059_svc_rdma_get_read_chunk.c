svc_rdma_get_read_chunk(struct rpcrdma_msg *rmsgp)
{
	struct rpcrdma_read_chunk *ch =
		(struct rpcrdma_read_chunk *)&rmsgp->rm_body.rm_chunks[0];

	if (ch->rc_discrim == xdr_zero)
		return NULL;
	return ch;
}
