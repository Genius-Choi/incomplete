static void srpt_cm_rej_recv(struct ib_cm_id *cm_id)
{
	pr_info("Received IB REJ for cm_id %p.\n", cm_id);
	srpt_drain_channel(cm_id);
}
