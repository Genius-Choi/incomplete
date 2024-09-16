static enum srpt_command_state srpt_set_cmd_state(struct srpt_send_ioctx *ioctx,
						  enum srpt_command_state new)
{
	enum srpt_command_state previous;
	unsigned long flags;

	BUG_ON(!ioctx);

	spin_lock_irqsave(&ioctx->spinlock, flags);
	previous = ioctx->state;
	if (previous != SRPT_STATE_DONE)
		ioctx->state = new;
	spin_unlock_irqrestore(&ioctx->spinlock, flags);

	return previous;
}
