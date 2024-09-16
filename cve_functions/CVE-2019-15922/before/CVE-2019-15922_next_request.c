static inline void next_request(blk_status_t err)
{
	unsigned long saved_flags;

	spin_lock_irqsave(&pf_spin_lock, saved_flags);
	pf_end_request(err);
	pf_busy = 0;
	pf_request();
	spin_unlock_irqrestore(&pf_spin_lock, saved_flags);
}
