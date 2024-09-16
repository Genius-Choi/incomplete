void rpc_free(void *buffer)
{
	size_t size;
	struct rpc_buffer *buf;

	if (!buffer)
		return;

	buf = container_of(buffer, struct rpc_buffer, data);
	size = buf->len;

	dprintk("RPC:       freeing buffer of size %zu at %p\n",
			size, buf);

	if (size <= RPC_BUFFER_MAXSIZE)
		mempool_free(buf, rpc_buffer_mempool);
	else
		kfree(buf);
}
