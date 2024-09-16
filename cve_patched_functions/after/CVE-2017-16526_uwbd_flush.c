void uwbd_flush(struct uwb_rc *rc)
{
	struct uwb_event *evt, *nxt;

	spin_lock_irq(&rc->uwbd.event_list_lock);
	list_for_each_entry_safe(evt, nxt, &rc->uwbd.event_list, list_node) {
		if (evt->rc == rc) {
			__uwb_rc_put(rc);
			list_del(&evt->list_node);
			if (evt->type == UWB_EVT_TYPE_NOTIF)
				kfree(evt->notif.rceb);
			kfree(evt);
		}
	}
	spin_unlock_irq(&rc->uwbd.event_list_lock);
}
