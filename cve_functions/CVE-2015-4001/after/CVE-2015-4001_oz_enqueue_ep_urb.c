static int oz_enqueue_ep_urb(struct oz_port *port, u8 ep_addr, int in_dir,
			struct urb *urb, u8 req_id)
{
	struct oz_urb_link *urbl;
	struct oz_endpoint *ep = NULL;
	int err = 0;

	if (ep_addr >= OZ_NB_ENDPOINTS) {
		oz_dbg(ON, "%s: Invalid endpoint number\n", __func__);
		return -EINVAL;
	}
	urbl = oz_alloc_urb_link();
	if (!urbl)
		return -ENOMEM;
	urbl->submit_counter = 0;
	urbl->urb = urb;
	urbl->req_id = req_id;
	urbl->ep_num = ep_addr;
	/* Hold lock while we insert the URB into the list within the
	 * endpoint structure.
	 */
	spin_lock_bh(&port->ozhcd->hcd_lock);
	/* If the urb has been unlinked while out of any list then
	 * complete it now.
	 */
	if (urb->unlinked) {
		spin_unlock_bh(&port->ozhcd->hcd_lock);
		oz_dbg(ON, "urb %p unlinked so complete immediately\n", urb);
		oz_complete_urb(port->ozhcd->hcd, urb, 0);
		oz_free_urb_link(urbl);
		return 0;
	}

	if (in_dir)
		ep = port->in_ep[ep_addr];
	else
		ep = port->out_ep[ep_addr];
	if (!ep) {
		err = -ENOMEM;
		goto out;
	}

	/*For interrupt endpoint check for buffered data
	* & complete urb
	*/
	if (((ep->attrib & USB_ENDPOINT_XFERTYPE_MASK) == USB_ENDPOINT_XFER_INT)
						 && ep->buffered_units > 0) {
		oz_free_urb_link(urbl);
		spin_unlock_bh(&port->ozhcd->hcd_lock);
		oz_complete_buffered_urb(port, ep, urb);
		return 0;
	}

	if (port->hpd) {
		list_add_tail(&urbl->link, &ep->urb_list);
		if (!in_dir && ep_addr && (ep->credit < 0)) {
			getrawmonotonic(&ep->timestamp);
			ep->credit = 0;
		}
	} else {
		err = -EPIPE;
	}
out:
	spin_unlock_bh(&port->ozhcd->hcd_lock);
	if (err)
		oz_free_urb_link(urbl);
	return err;
}
