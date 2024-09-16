static void ipmi_timeout(struct timer_list *unused)
{
	struct ipmi_smi *intf;
	int nt = 0, index;

	if (atomic_read(&stop_operation))
		return;

	index = srcu_read_lock(&ipmi_interfaces_srcu);
	list_for_each_entry_rcu(intf, &ipmi_interfaces, link) {
		int lnt = 0;

		if (atomic_read(&intf->event_waiters)) {
			intf->ticks_to_req_ev--;
			if (intf->ticks_to_req_ev == 0) {
				ipmi_request_event(intf);
				intf->ticks_to_req_ev = IPMI_REQUEST_EV_TIME;
			}
			lnt++;
		}

		lnt += ipmi_timeout_handler(intf, IPMI_TIMEOUT_TIME);

		lnt = !!lnt;
		if (lnt != intf->last_needs_timer &&
					intf->handlers->set_need_watch)
			intf->handlers->set_need_watch(intf->send_info, lnt);
		intf->last_needs_timer = lnt;

		nt += lnt;
	}
	srcu_read_unlock(&ipmi_interfaces_srcu, index);

	if (nt)
		mod_timer(&ipmi_timer, jiffies + IPMI_TIMEOUT_JIFFIES);
}
