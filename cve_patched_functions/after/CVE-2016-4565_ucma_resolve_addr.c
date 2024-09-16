static ssize_t ucma_resolve_addr(struct ucma_file *file,
				 const char __user *inbuf,
				 int in_len, int out_len)
{
	struct rdma_ucm_resolve_addr cmd;
	struct sockaddr *src, *dst;
	struct ucma_context *ctx;
	int ret;

	if (copy_from_user(&cmd, inbuf, sizeof(cmd)))
		return -EFAULT;

	src = (struct sockaddr *) &cmd.src_addr;
	dst = (struct sockaddr *) &cmd.dst_addr;
	if (cmd.reserved || (cmd.src_size && (cmd.src_size != rdma_addr_size(src))) ||
	    !cmd.dst_size || (cmd.dst_size != rdma_addr_size(dst)))
		return -EINVAL;

	ctx = ucma_get_ctx(file, cmd.id);
	if (IS_ERR(ctx))
		return PTR_ERR(ctx);

	ret = rdma_resolve_addr(ctx->cm_id, src, dst, cmd.timeout_ms);
	ucma_put_ctx(ctx);
	return ret;
}
