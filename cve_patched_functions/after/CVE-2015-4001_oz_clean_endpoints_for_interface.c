static void oz_clean_endpoints_for_interface(struct usb_hcd *hcd,
			struct oz_port *port, int if_ix)
{
	struct oz_hcd *ozhcd = port->ozhcd;
	unsigned mask;
	int i;
	LIST_HEAD(ep_list);
	struct oz_endpoint *ep, *n;

	oz_dbg(ON, "Deleting endpoints for interface %d\n", if_ix);
	if (if_ix >= port->num_iface)
		return;
	spin_lock_bh(&ozhcd->hcd_lock);
	mask = port->iface[if_ix].ep_mask;
	port->iface[if_ix].ep_mask = 0;
	for (i = 0; i < OZ_NB_ENDPOINTS; i++) {
		struct list_head *e;
		/* Gather OUT endpoints.
		 */
		if ((mask & (1<<i)) && port->out_ep[i]) {
			e = &port->out_ep[i]->link;
			port->out_ep[i] = NULL;
			/* Remove from isoc list if present.
			 */
			list_move_tail(e, &ep_list);
		}
		/* Gather IN endpoints.
		 */
		if ((mask & (1<<(i+OZ_NB_ENDPOINTS))) && port->in_ep[i]) {
			e = &port->in_ep[i]->link;
			port->in_ep[i] = NULL;
			list_move_tail(e, &ep_list);
		}
	}
	spin_unlock_bh(&ozhcd->hcd_lock);
	list_for_each_entry_safe(ep, n, &ep_list, link) {
		list_del_init(&ep->link);
		oz_ep_free(port, ep);
	}
}
