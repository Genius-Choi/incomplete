static void srpt_drain_channel(struct ib_cm_id *cm_id)
{
	struct srpt_device *sdev;
	struct srpt_rdma_ch *ch;
	int ret;
	bool do_reset = false;

	WARN_ON_ONCE(irqs_disabled());

	sdev = cm_id->context;
	BUG_ON(!sdev);
	spin_lock_irq(&sdev->spinlock);
	list_for_each_entry(ch, &sdev->rch_list, list) {
		if (ch->cm_id == cm_id) {
			do_reset = srpt_test_and_set_ch_state(ch,
					CH_CONNECTING, CH_DRAINING) ||
				   srpt_test_and_set_ch_state(ch,
					CH_LIVE, CH_DRAINING) ||
				   srpt_test_and_set_ch_state(ch,
					CH_DISCONNECTING, CH_DRAINING);
			break;
		}
	}
	spin_unlock_irq(&sdev->spinlock);

	if (do_reset) {
		if (ch->sess)
			srpt_shutdown_session(ch->sess);

		ret = srpt_ch_qp_err(ch);
		if (ret < 0)
			pr_err("Setting queue pair in error state"
			       " failed: %d\n", ret);
	}
}
