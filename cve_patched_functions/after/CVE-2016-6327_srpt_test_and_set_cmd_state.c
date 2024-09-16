static bool srpt_test_and_set_cmd_state(struct srpt_send_ioctx *ioctx,
					enum srpt_command_state old,
					enum srpt_command_state new)
{
	enum srpt_command_state previous;
	unsigned long flags;

	WARN_ON(!ioctx);
	WARN_ON(old == SRPT_STATE_DONE);
	WARN_ON(new == SRPT_STATE_NEW);

	spin_lock_irqsave(&ioctx->spinlock, flags);
	previous = ioctx->state;
	if (previous == old)
		ioctx->state = new;
	spin_unlock_irqrestore(&ioctx->spinlock, flags);
	return previous == old;
}
