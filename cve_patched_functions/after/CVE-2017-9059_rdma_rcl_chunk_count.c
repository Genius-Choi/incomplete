rdma_rcl_chunk_count(struct rpcrdma_read_chunk *ch)
{
	unsigned int count;

	for (count = 0; ch->rc_discrim != xdr_zero; ch++)
		count++;
	return count;
}
