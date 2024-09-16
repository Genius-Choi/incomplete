static ssize_t ib_ucm_create_id(struct ib_ucm_file *file,
				const char __user *inbuf,
				int in_len, int out_len)
{
	struct ib_ucm_create_id cmd;
	struct ib_ucm_create_id_resp resp;
	struct ib_ucm_context *ctx;
	int result;

	if (out_len < sizeof(resp))
		return -ENOSPC;

	if (copy_from_user(&cmd, inbuf, sizeof(cmd)))
		return -EFAULT;

	mutex_lock(&file->file_mutex);
	ctx = ib_ucm_ctx_alloc(file);
	mutex_unlock(&file->file_mutex);
	if (!ctx)
		return -ENOMEM;

	ctx->uid = cmd.uid;
	ctx->cm_id = ib_create_cm_id(file->device->ib_dev,
				     ib_ucm_event_handler, ctx);
	if (IS_ERR(ctx->cm_id)) {
		result = PTR_ERR(ctx->cm_id);
		goto err1;
	}

	resp.id = ctx->id;
	if (copy_to_user((void __user *)(unsigned long)cmd.response,
			 &resp, sizeof(resp))) {
		result = -EFAULT;
		goto err2;
	}
	return 0;

err2:
	ib_destroy_cm_id(ctx->cm_id);
err1:
	mutex_lock(&ctx_id_mutex);
	idr_remove(&ctx_id_table, ctx->id);
	mutex_unlock(&ctx_id_mutex);
	kfree(ctx);
	return result;
}
