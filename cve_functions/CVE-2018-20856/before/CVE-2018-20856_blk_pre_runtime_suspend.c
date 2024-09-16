int blk_pre_runtime_suspend(struct request_queue *q)
{
	int ret = 0;

	if (!q->dev)
		return ret;

	spin_lock_irq(q->queue_lock);
	if (q->nr_pending) {
		ret = -EBUSY;
		pm_runtime_mark_last_busy(q->dev);
	} else {
		q->rpm_status = RPM_SUSPENDING;
	}
	spin_unlock_irq(q->queue_lock);
	return ret;
}
