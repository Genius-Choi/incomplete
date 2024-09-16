static enum rdma_ch_state srpt_get_ch_state(struct srpt_rdma_ch *ch)
{
	unsigned long flags;
	enum rdma_ch_state state;

	spin_lock_irqsave(&ch->spinlock, flags);
	state = ch->state;
	spin_unlock_irqrestore(&ch->spinlock, flags);
	return state;
}
