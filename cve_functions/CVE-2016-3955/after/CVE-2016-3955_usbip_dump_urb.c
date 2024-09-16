void usbip_dump_urb(struct urb *urb)
{
	struct device *dev;

	if (!urb) {
		pr_debug("urb: null pointer!!\n");
		return;
	}

	if (!urb->dev) {
		pr_debug("urb->dev: null pointer!!\n");
		return;
	}

	dev = &urb->dev->dev;

	dev_dbg(dev, "   urb                   :%p\n", urb);
	dev_dbg(dev, "   dev                   :%p\n", urb->dev);

	usbip_dump_usb_device(urb->dev);

	dev_dbg(dev, "   pipe                  :%08x ", urb->pipe);

	usbip_dump_pipe(urb->pipe);

	dev_dbg(dev, "   status                :%d\n", urb->status);
	dev_dbg(dev, "   transfer_flags        :%08X\n", urb->transfer_flags);
	dev_dbg(dev, "   transfer_buffer       :%p\n", urb->transfer_buffer);
	dev_dbg(dev, "   transfer_buffer_length:%d\n",
						urb->transfer_buffer_length);
	dev_dbg(dev, "   actual_length         :%d\n", urb->actual_length);
	dev_dbg(dev, "   setup_packet          :%p\n", urb->setup_packet);

	if (urb->setup_packet && usb_pipetype(urb->pipe) == PIPE_CONTROL)
		usbip_dump_usb_ctrlrequest(
			(struct usb_ctrlrequest *)urb->setup_packet);

	dev_dbg(dev, "   start_frame           :%d\n", urb->start_frame);
	dev_dbg(dev, "   number_of_packets     :%d\n", urb->number_of_packets);
	dev_dbg(dev, "   interval              :%d\n", urb->interval);
	dev_dbg(dev, "   error_count           :%d\n", urb->error_count);
	dev_dbg(dev, "   context               :%p\n", urb->context);
	dev_dbg(dev, "   complete              :%p\n", urb->complete);
}
