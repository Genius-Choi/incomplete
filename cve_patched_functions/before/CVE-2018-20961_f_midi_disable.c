static void f_midi_disable(struct usb_function *f)
{
	struct f_midi *midi = func_to_midi(f);
	struct usb_composite_dev *cdev = f->config->cdev;
	struct usb_request *req = NULL;

	DBG(cdev, "disable\n");

	/*
	 * just disable endpoints, forcing completion of pending i/o.
	 * all our completion handlers free their requests in this case.
	 */
	usb_ep_disable(midi->in_ep);
	usb_ep_disable(midi->out_ep);

	/* release IN requests */
	while (kfifo_get(&midi->in_req_fifo, &req))
		free_ep_req(midi->in_ep, req);

	f_midi_drop_out_substreams(midi);
}
