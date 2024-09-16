static void nfc_llcp_symm_timer(struct timer_list *t)
{
	struct nfc_llcp_local *local = from_timer(local, t, link_timer);

	pr_err("SYMM timeout\n");

	schedule_work(&local->timeout_work);
}
