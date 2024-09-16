static int xen_netbk_kthread(void *data)
{
	struct xen_netbk *netbk = data;
	while (!kthread_should_stop()) {
		wait_event_interruptible(netbk->wq,
				rx_work_todo(netbk) ||
				tx_work_todo(netbk) ||
				kthread_should_stop());
		cond_resched();

		if (kthread_should_stop())
			break;

		if (rx_work_todo(netbk))
			xen_netbk_rx_action(netbk);

		if (tx_work_todo(netbk))
			xen_netbk_tx_action(netbk);
	}

	return 0;
}
