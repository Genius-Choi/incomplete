srpt_set_ch_state(struct srpt_rdma_ch *ch, enum rdma_ch_state new_state)
{
	unsigned long flags;
	enum rdma_ch_state prev;

	spin_lock_irqsave(&ch->spinlock, flags);
	prev = ch->state;
	ch->state = new_state;
	spin_unlock_irqrestore(&ch->spinlock, flags);
	return prev;
}
