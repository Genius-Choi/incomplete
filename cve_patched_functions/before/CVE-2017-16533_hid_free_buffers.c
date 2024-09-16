static void hid_free_buffers(struct usb_device *dev, struct hid_device *hid)
{
	struct usbhid_device *usbhid = hid->driver_data;

	usb_free_coherent(dev, usbhid->bufsize, usbhid->inbuf, usbhid->inbuf_dma);
	usb_free_coherent(dev, usbhid->bufsize, usbhid->outbuf, usbhid->outbuf_dma);
	kfree(usbhid->cr);
	usb_free_coherent(dev, usbhid->bufsize, usbhid->ctrlbuf, usbhid->ctrlbuf_dma);
}
