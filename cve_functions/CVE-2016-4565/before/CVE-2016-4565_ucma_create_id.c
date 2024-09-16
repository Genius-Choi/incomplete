static ssize_t ucma_create_id(struct ucma_file *file, const char __user *inbuf,
			      int in_len, int out_len)
{
	struct rdma_ucm_create_id cmd;
	struct rdma_ucm_create_id_resp resp;
	struct ucma_context *ctx;
	enum ib_qp_type qp_type;
	int ret;

	if (out_len < sizeof(resp))
		return -ENOSPC;

	if (copy_from_user(&cmd, inbuf, sizeof(cmd)))
		return -EFAULT;

	ret = ucma_get_qp_type(&cmd, &qp_type);
	if (ret)
		return ret;

	mutex_lock(&file->mut);
	ctx = ucma_alloc_ctx(file);
	mutex_unlock(&file->mut);
	if (!ctx)
		return -ENOMEM;

	ctx->uid = cmd.uid;
	ctx->cm_id = rdma_create_id(current->nsproxy->net_ns,
				    ucma_event_handler, ctx, cmd.ps, qp_type);
	if (IS_ERR(ctx->cm_id)) {
		ret = PTR_ERR(ctx->cm_id);
		goto err1;
	}

	resp.id = ctx->id;
	if (copy_to_user((void __user *)(unsigned long)cmd.response,
			 &resp, sizeof(resp))) {
		ret = -EFAULT;
		goto err2;
	}
	return 0;

err2:
	rdma_destroy_id(ctx->cm_id);
err1:
	mutex_lock(&mut);
	idr_remove(&ctx_idr, ctx->id);
	mutex_unlock(&mut);
	kfree(ctx);
	return ret;
}
