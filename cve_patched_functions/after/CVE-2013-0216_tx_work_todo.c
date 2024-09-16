static inline int tx_work_todo(struct xen_netbk *netbk)
{

	if (((nr_pending_reqs(netbk) + MAX_SKB_FRAGS) < MAX_PENDING_REQS) &&
			!list_empty(&netbk->net_schedule_list))
		return 1;

	return 0;
}
