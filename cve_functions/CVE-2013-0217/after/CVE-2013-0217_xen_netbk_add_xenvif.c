void xen_netbk_add_xenvif(struct xenvif *vif)
{
	int i;
	int min_netfront_count;
	int min_group = 0;
	struct xen_netbk *netbk;

	min_netfront_count = atomic_read(&xen_netbk[0].netfront_count);
	for (i = 0; i < xen_netbk_group_nr; i++) {
		int netfront_count = atomic_read(&xen_netbk[i].netfront_count);
		if (netfront_count < min_netfront_count) {
			min_group = i;
			min_netfront_count = netfront_count;
		}
	}

	netbk = &xen_netbk[min_group];

	vif->netbk = netbk;
	atomic_inc(&netbk->netfront_count);
}
