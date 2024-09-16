static void srpt_srq_event(struct ib_event *event, void *ctx)
{
	pr_info("SRQ event %d\n", event->event);
}
