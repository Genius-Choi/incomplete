static void xen_netbk_kick_thread(struct xen_netbk *netbk)
{
	wake_up(&netbk->wq);
}
