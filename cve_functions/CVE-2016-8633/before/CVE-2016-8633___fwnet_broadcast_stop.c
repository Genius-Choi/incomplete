static void __fwnet_broadcast_stop(struct fwnet_device *dev)
{
	unsigned u;

	if (dev->broadcast_state != FWNET_BROADCAST_ERROR) {
		for (u = 0; u < FWNET_ISO_PAGE_COUNT; u++)
			kunmap(dev->broadcast_rcv_buffer.pages[u]);
		fw_iso_buffer_destroy(&dev->broadcast_rcv_buffer, dev->card);
	}
	if (dev->broadcast_rcv_context) {
		fw_iso_context_destroy(dev->broadcast_rcv_context);
		dev->broadcast_rcv_context = NULL;
	}
	kfree(dev->broadcast_rcv_buffer_ptrs);
	dev->broadcast_rcv_buffer_ptrs = NULL;
	dev->broadcast_state = FWNET_BROADCAST_ERROR;
}
