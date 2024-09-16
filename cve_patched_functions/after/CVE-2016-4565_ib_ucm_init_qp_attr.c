static ssize_t ib_ucm_init_qp_attr(struct ib_ucm_file *file,
				   const char __user *inbuf,
				   int in_len, int out_len)
{
	struct ib_uverbs_qp_attr resp;
	struct ib_ucm_init_qp_attr cmd;
	struct ib_ucm_context *ctx;
	struct ib_qp_attr qp_attr;
	int result = 0;

	if (out_len < sizeof(resp))
		return -ENOSPC;

	if (copy_from_user(&cmd, inbuf, sizeof(cmd)))
		return -EFAULT;

	ctx = ib_ucm_ctx_get(file, cmd.id);
	if (IS_ERR(ctx))
		return PTR_ERR(ctx);

	resp.qp_attr_mask = 0;
	memset(&qp_attr, 0, sizeof qp_attr);
	qp_attr.qp_state = cmd.qp_state;
	result = ib_cm_init_qp_attr(ctx->cm_id, &qp_attr, &resp.qp_attr_mask);
	if (result)
		goto out;

	ib_copy_qp_attr_to_user(&resp, &qp_attr);

	if (copy_to_user((void __user *)(unsigned long)cmd.response,
			 &resp, sizeof(resp)))
		result = -EFAULT;

out:
	ib_ucm_ctx_put(ctx);
	return result;
}
