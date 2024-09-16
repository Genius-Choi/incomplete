static int srpt_shutdown_session(struct se_session *se_sess)
{
	struct srpt_rdma_ch *ch = se_sess->fabric_sess_ptr;
	unsigned long flags;

	spin_lock_irqsave(&ch->spinlock, flags);
	if (ch->in_shutdown) {
		spin_unlock_irqrestore(&ch->spinlock, flags);
		return true;
	}

	ch->in_shutdown = true;
	target_sess_cmd_list_set_waiting(se_sess);
	spin_unlock_irqrestore(&ch->spinlock, flags);

	return true;
}
