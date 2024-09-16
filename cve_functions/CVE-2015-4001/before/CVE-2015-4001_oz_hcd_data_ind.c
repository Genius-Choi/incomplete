void oz_hcd_data_ind(void *hport, u8 endpoint, const u8 *data, int data_len)
{
	struct oz_port *port = (struct oz_port *)hport;
	struct oz_endpoint *ep;
	struct oz_hcd *ozhcd = port->ozhcd;

	spin_lock_bh(&ozhcd->hcd_lock);
	ep = port->in_ep[endpoint & USB_ENDPOINT_NUMBER_MASK];
	if (ep == NULL)
		goto done;
	switch (ep->attrib & USB_ENDPOINT_XFERTYPE_MASK) {
	case USB_ENDPOINT_XFER_INT:
	case USB_ENDPOINT_XFER_BULK:
		if (!list_empty(&ep->urb_list)) {
			struct oz_urb_link *urbl =
				list_first_entry(&ep->urb_list,
					struct oz_urb_link, link);
			struct urb *urb;
			int copy_len;

			list_del_init(&urbl->link);
			spin_unlock_bh(&ozhcd->hcd_lock);
			urb = urbl->urb;
			oz_free_urb_link(urbl);
			if (data_len <= urb->transfer_buffer_length)
				copy_len = data_len;
			else
				copy_len = urb->transfer_buffer_length;
			memcpy(urb->transfer_buffer, data, copy_len);
			urb->actual_length = copy_len;
			oz_complete_urb(port->ozhcd->hcd, urb, 0);
			return;
		}
		oz_dbg(ON, "buffering frame as URB is not available\n");
		oz_hcd_buffer_data(ep, data, data_len);
		break;
	case USB_ENDPOINT_XFER_ISOC:
		oz_hcd_buffer_data(ep, data, data_len);
		break;
	}
done:
	spin_unlock_bh(&ozhcd->hcd_lock);
}
