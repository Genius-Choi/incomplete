static struct srpt_rdma_ch *srpt_find_channel(struct srpt_device *sdev,
					      struct ib_cm_id *cm_id)
{
	struct srpt_rdma_ch *ch;
	bool found;

	WARN_ON_ONCE(irqs_disabled());
	BUG_ON(!sdev);

	found = false;
	spin_lock_irq(&sdev->spinlock);
	list_for_each_entry(ch, &sdev->rch_list, list) {
		if (ch->cm_id == cm_id) {
			found = true;
			break;
		}
	}
	spin_unlock_irq(&sdev->spinlock);

	return found ? ch : NULL;
}
