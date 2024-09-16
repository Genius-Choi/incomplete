static void check_carrier(struct work_struct *work)
{
	pegasus_t *pegasus = container_of(work, pegasus_t, carrier_check.work);
	set_carrier(pegasus->net);
	if (!(pegasus->flags & PEGASUS_UNPLUG)) {
		queue_delayed_work(pegasus_workqueue, &pegasus->carrier_check,
			CARRIER_CHECK_DELAY);
	}
}
