static void srpt_cm_dreq_recv(struct ib_cm_id *cm_id)
{
	struct srpt_rdma_ch *ch;
	unsigned long flags;
	bool send_drep = false;

	ch = srpt_find_channel(cm_id->context, cm_id);
	BUG_ON(!ch);

	pr_debug("cm_id= %p ch->state= %d\n", cm_id, srpt_get_ch_state(ch));

	spin_lock_irqsave(&ch->spinlock, flags);
	switch (ch->state) {
	case CH_CONNECTING:
	case CH_LIVE:
		send_drep = true;
		ch->state = CH_DISCONNECTING;
		break;
	case CH_DISCONNECTING:
	case CH_DRAINING:
	case CH_RELEASING:
		WARN(true, "unexpected channel state %d\n", ch->state);
		break;
	}
	spin_unlock_irqrestore(&ch->spinlock, flags);

	if (send_drep) {
		if (ib_send_cm_drep(ch->cm_id, NULL, 0) < 0)
			pr_err("Sending IB DREP failed.\n");
		pr_info("Received DREQ and sent DREP for session %s.\n",
			ch->sess_name);
	}
}
