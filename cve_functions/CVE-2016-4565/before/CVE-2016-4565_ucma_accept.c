static ssize_t ucma_accept(struct ucma_file *file, const char __user *inbuf,
			   int in_len, int out_len)
{
	struct rdma_ucm_accept cmd;
	struct rdma_conn_param conn_param;
	struct ucma_context *ctx;
	int ret;

	if (copy_from_user(&cmd, inbuf, sizeof(cmd)))
		return -EFAULT;

	ctx = ucma_get_ctx(file, cmd.id);
	if (IS_ERR(ctx))
		return PTR_ERR(ctx);

	if (cmd.conn_param.valid) {
		ucma_copy_conn_param(ctx->cm_id, &conn_param, &cmd.conn_param);
		mutex_lock(&file->mut);
		ret = rdma_accept(ctx->cm_id, &conn_param);
		if (!ret)
			ctx->uid = cmd.uid;
		mutex_unlock(&file->mut);
	} else
		ret = rdma_accept(ctx->cm_id, NULL);

	ucma_put_ctx(ctx);
	return ret;
}
