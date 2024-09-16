static void srpt_close_ch(struct srpt_rdma_ch *ch)
{
	struct srpt_device *sdev;

	sdev = ch->sport->sdev;
	spin_lock_irq(&sdev->spinlock);
	__srpt_close_ch(ch);
	spin_unlock_irq(&sdev->spinlock);
}
