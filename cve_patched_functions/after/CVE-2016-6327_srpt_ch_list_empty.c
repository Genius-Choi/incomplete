static int srpt_ch_list_empty(struct srpt_device *sdev)
{
	int res;

	spin_lock_irq(&sdev->spinlock);
	res = list_empty(&sdev->rch_list);
	spin_unlock_irq(&sdev->spinlock);

	return res;
}
