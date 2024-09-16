static long timerfd_ioctl(struct file *file, unsigned int cmd, unsigned long arg)
{
	struct timerfd_ctx *ctx = file->private_data;
	int ret = 0;

	switch (cmd) {
	case TFD_IOC_SET_TICKS: {
		u64 ticks;

		if (copy_from_user(&ticks, (u64 __user *)arg, sizeof(ticks)))
			return -EFAULT;
		if (!ticks)
			return -EINVAL;

		spin_lock_irq(&ctx->wqh.lock);
		if (!timerfd_canceled(ctx)) {
			ctx->ticks = ticks;
			wake_up_locked(&ctx->wqh);
		} else
			ret = -ECANCELED;
		spin_unlock_irq(&ctx->wqh.lock);
		break;
	}
	default:
		ret = -ENOTTY;
		break;
	}

	return ret;
}
