static int srpt_release_sdev(struct srpt_device *sdev)
{
	struct srpt_rdma_ch *ch, *tmp_ch;
	int res;

	WARN_ON_ONCE(irqs_disabled());

	BUG_ON(!sdev);

	spin_lock_irq(&sdev->spinlock);
	list_for_each_entry_safe(ch, tmp_ch, &sdev->rch_list, list)
		__srpt_close_ch(ch);
	spin_unlock_irq(&sdev->spinlock);

	res = wait_event_interruptible(sdev->ch_releaseQ,
				       srpt_ch_list_empty(sdev));
	if (res)
		pr_err("%s: interrupted.\n", __func__);

	return 0;
}
