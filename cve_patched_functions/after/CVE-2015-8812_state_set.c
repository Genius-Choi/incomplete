static void state_set(struct iwch_ep_common *epc, enum iwch_ep_state new)
{
	unsigned long flags;

	spin_lock_irqsave(&epc->lock, flags);
	PDBG("%s - %s -> %s\n", __func__, states[epc->state], states[new]);
	__state_set(epc, new);
	spin_unlock_irqrestore(&epc->lock, flags);
	return;
}
