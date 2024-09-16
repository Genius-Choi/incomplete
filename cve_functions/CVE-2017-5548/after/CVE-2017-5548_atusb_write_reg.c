static int atusb_write_reg(struct atusb *atusb, uint8_t reg, uint8_t value)
{
	struct usb_device *usb_dev = atusb->usb_dev;

	dev_dbg(&usb_dev->dev, "atusb_write_reg: 0x%02x <- 0x%02x\n",
		reg, value);
	return atusb_control_msg(atusb, usb_sndctrlpipe(usb_dev, 0),
				 ATUSB_REG_WRITE, ATUSB_REQ_TO_DEV,
				 value, reg, NULL, 0, 1000);
}
