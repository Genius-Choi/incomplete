static ssize_t ib_ucm_notify(struct ib_ucm_file *file,
			     const char __user *inbuf,
			     int in_len, int out_len)
{
	struct ib_ucm_notify cmd;
	struct ib_ucm_context *ctx;
	int result;

	if (copy_from_user(&cmd, inbuf, sizeof(cmd)))
		return -EFAULT;

	ctx = ib_ucm_ctx_get(file, cmd.id);
	if (IS_ERR(ctx))
		return PTR_ERR(ctx);

	result = ib_cm_notify(ctx->cm_id, (enum ib_event_type) cmd.event);
	ib_ucm_ctx_put(ctx);
	return result;
}
