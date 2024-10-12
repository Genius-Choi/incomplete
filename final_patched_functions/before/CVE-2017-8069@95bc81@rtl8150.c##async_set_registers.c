static int async_set_registers(rtl8150_t *dev, u16 indx, u16 size, u16 reg)
{
	int res = -ENOMEM;
	struct urb *async_urb;
	struct async_req *req;

	req = kmalloc(sizeof(struct async_req), GFP_ATOMIC);
	if (req == NULL)
		return res;
	async_urb = usb_alloc_urb(0, GFP_ATOMIC);
	if (async_urb == NULL) {
		kfree(req);
		return res;
	}
	req->rx_creg = cpu_to_le16(reg);
	req->dr.bRequestType = RTL8150_REQT_WRITE;
	req->dr.bRequest = RTL8150_REQ_SET_REGS;
	req->dr.wIndex = 0;
	req->dr.wValue = cpu_to_le16(indx);
	req->dr.wLength = cpu_to_le16(size);
	usb_fill_control_urb(async_urb, dev->udev,
	                     usb_sndctrlpipe(dev->udev, 0), (void *)&req->dr,
			     &req->rx_creg, size, async_set_reg_cb, req);
	res = usb_submit_urb(async_urb, GFP_ATOMIC);
	if (res) {
		if (res == -ENODEV)
			netif_device_detach(dev->netdev);
		dev_err(&dev->udev->dev, "%s failed with %d\n", __func__, res);
	}
	return res;
}
