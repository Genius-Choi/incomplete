static void xen_netbk_tx_action(struct xen_netbk *netbk)
{
	unsigned nr_gops;

	nr_gops = xen_netbk_tx_build_gops(netbk);

	if (nr_gops == 0)
		return;

	gnttab_batch_copy(netbk->tx_copy_ops, nr_gops);

	xen_netbk_tx_submit(netbk);
}
