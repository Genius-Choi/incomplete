int i8042_remove_filter(bool (*filter)(unsigned char data, unsigned char str,
				       struct serio *port))
{
	unsigned long flags;
	int ret = 0;

	spin_lock_irqsave(&i8042_lock, flags);

	if (i8042_platform_filter != filter) {
		ret = -EINVAL;
		goto out;
	}

	i8042_platform_filter = NULL;

out:
	spin_unlock_irqrestore(&i8042_lock, flags);
	return ret;
}
