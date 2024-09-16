srpt_test_and_set_ch_state(struct srpt_rdma_ch *ch, enum rdma_ch_state old,
			   enum rdma_ch_state new)
{
	unsigned long flags;
	enum rdma_ch_state prev;

	spin_lock_irqsave(&ch->spinlock, flags);
	prev = ch->state;
	if (prev == old)
		ch->state = new;
	spin_unlock_irqrestore(&ch->spinlock, flags);
	return prev == old;
}
