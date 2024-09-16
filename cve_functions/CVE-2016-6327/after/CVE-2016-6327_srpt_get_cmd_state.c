static enum srpt_command_state srpt_get_cmd_state(struct srpt_send_ioctx *ioctx)
{
	enum srpt_command_state state;
	unsigned long flags;

	BUG_ON(!ioctx);

	spin_lock_irqsave(&ioctx->spinlock, flags);
	state = ioctx->state;
	spin_unlock_irqrestore(&ioctx->spinlock, flags);
	return state;
}
