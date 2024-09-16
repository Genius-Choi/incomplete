static void unlink_all_urbs(pegasus_t *pegasus)
{
	usb_kill_urb(pegasus->intr_urb);
	usb_kill_urb(pegasus->tx_urb);
	usb_kill_urb(pegasus->rx_urb);
}
