static void srpt_close_session(struct se_session *se_sess)
{
	DECLARE_COMPLETION_ONSTACK(release_done);
	struct srpt_rdma_ch *ch;
	struct srpt_device *sdev;
	unsigned long res;

	ch = se_sess->fabric_sess_ptr;
	WARN_ON(ch->sess != se_sess);

	pr_debug("ch %p state %d\n", ch, srpt_get_ch_state(ch));

	sdev = ch->sport->sdev;
	spin_lock_irq(&sdev->spinlock);
	BUG_ON(ch->release_done);
	ch->release_done = &release_done;
	__srpt_close_ch(ch);
	spin_unlock_irq(&sdev->spinlock);

	res = wait_for_completion_timeout(&release_done, 60 * HZ);
	WARN_ON(res == 0);
}
