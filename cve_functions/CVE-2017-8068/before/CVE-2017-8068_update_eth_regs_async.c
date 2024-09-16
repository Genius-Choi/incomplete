static int update_eth_regs_async(pegasus_t *pegasus)
{
	int ret = -ENOMEM;
	struct urb *async_urb;
	struct usb_ctrlrequest *req;

	req = kmalloc(sizeof(struct usb_ctrlrequest), GFP_ATOMIC);
	if (req == NULL)
		return ret;

	async_urb = usb_alloc_urb(0, GFP_ATOMIC);
	if (async_urb == NULL) {
		kfree(req);
		return ret;
	}
	req->bRequestType = PEGASUS_REQT_WRITE;
	req->bRequest = PEGASUS_REQ_SET_REGS;
	req->wValue = cpu_to_le16(0);
	req->wIndex = cpu_to_le16(EthCtrl0);
	req->wLength = cpu_to_le16(3);

	usb_fill_control_urb(async_urb, pegasus->usb,
			     usb_sndctrlpipe(pegasus->usb, 0), (void *)req,
			     pegasus->eth_regs, 3, async_ctrl_callback, req);

	ret = usb_submit_urb(async_urb, GFP_ATOMIC);
	if (ret) {
		if (ret == -ENODEV)
			netif_device_detach(pegasus->net);
		netif_err(pegasus, drv, pegasus->net,
			  "%s returned %d\n", __func__, ret);
	}
	return ret;
}
