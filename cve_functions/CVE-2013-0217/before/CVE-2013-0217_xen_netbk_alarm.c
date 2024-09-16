static void xen_netbk_alarm(unsigned long data)
{
	struct xen_netbk *netbk = (struct xen_netbk *)data;
	xen_netbk_kick_thread(netbk);
}
