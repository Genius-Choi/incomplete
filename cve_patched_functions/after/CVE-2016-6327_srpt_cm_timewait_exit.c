static void srpt_cm_timewait_exit(struct ib_cm_id *cm_id)
{
	pr_info("Received IB TimeWait exit for cm_id %p.\n", cm_id);
	srpt_drain_channel(cm_id);
}
