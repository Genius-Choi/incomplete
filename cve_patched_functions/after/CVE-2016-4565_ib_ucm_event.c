static ssize_t ib_ucm_event(struct ib_ucm_file *file,
			    const char __user *inbuf,
			    int in_len, int out_len)
{
	struct ib_ucm_context *ctx;
	struct ib_ucm_event_get cmd;
	struct ib_ucm_event *uevent;
	int result = 0;

	if (out_len < sizeof(struct ib_ucm_event_resp))
		return -ENOSPC;

	if (copy_from_user(&cmd, inbuf, sizeof(cmd)))
		return -EFAULT;

	mutex_lock(&file->file_mutex);
	while (list_empty(&file->events)) {
		mutex_unlock(&file->file_mutex);

		if (file->filp->f_flags & O_NONBLOCK)
			return -EAGAIN;

		if (wait_event_interruptible(file->poll_wait,
					     !list_empty(&file->events)))
			return -ERESTARTSYS;

		mutex_lock(&file->file_mutex);
	}

	uevent = list_entry(file->events.next, struct ib_ucm_event, file_list);

	if (ib_ucm_new_cm_id(uevent->resp.event)) {
		ctx = ib_ucm_ctx_alloc(file);
		if (!ctx) {
			result = -ENOMEM;
			goto done;
		}

		ctx->cm_id = uevent->cm_id;
		ctx->cm_id->context = ctx;
		uevent->resp.id = ctx->id;
	}

	if (copy_to_user((void __user *)(unsigned long)cmd.response,
			 &uevent->resp, sizeof(uevent->resp))) {
		result = -EFAULT;
		goto done;
	}

	if (uevent->data) {
		if (cmd.data_len < uevent->data_len) {
			result = -ENOMEM;
			goto done;
		}
		if (copy_to_user((void __user *)(unsigned long)cmd.data,
				 uevent->data, uevent->data_len)) {
			result = -EFAULT;
			goto done;
		}
	}

	if (uevent->info) {
		if (cmd.info_len < uevent->info_len) {
			result = -ENOMEM;
			goto done;
		}
		if (copy_to_user((void __user *)(unsigned long)cmd.info,
				 uevent->info, uevent->info_len)) {
			result = -EFAULT;
			goto done;
		}
	}

	list_del(&uevent->file_list);
	list_del(&uevent->ctx_list);
	uevent->ctx->events_reported++;

	kfree(uevent->data);
	kfree(uevent->info);
	kfree(uevent);
done:
	mutex_unlock(&file->file_mutex);
	return result;
}
