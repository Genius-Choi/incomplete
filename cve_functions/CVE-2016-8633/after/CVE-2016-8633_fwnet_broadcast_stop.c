static void fwnet_broadcast_stop(struct fwnet_device *dev)
{
	if (dev->broadcast_state == FWNET_BROADCAST_ERROR)
		return;
	fw_iso_context_stop(dev->broadcast_rcv_context);
	__fwnet_broadcast_stop(dev);
}
