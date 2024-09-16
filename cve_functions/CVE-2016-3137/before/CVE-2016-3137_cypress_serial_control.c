static int cypress_serial_control(struct tty_struct *tty,
	struct usb_serial_port *port, speed_t baud_rate, int data_bits,
	int stop_bits, int parity_enable, int parity_type, int reset,
	int cypress_request_type)
{
	int new_baudrate = 0, retval = 0, tries = 0;
	struct cypress_private *priv;
	struct device *dev = &port->dev;
	u8 *feature_buffer;
	const unsigned int feature_len = 5;
	unsigned long flags;

	priv = usb_get_serial_port_data(port);

	if (!priv->comm_is_ok)
		return -ENODEV;

	feature_buffer = kcalloc(feature_len, sizeof(u8), GFP_KERNEL);
	if (!feature_buffer)
		return -ENOMEM;

	switch (cypress_request_type) {
	case CYPRESS_SET_CONFIG:
		/* 0 means 'Hang up' so doesn't change the true bit rate */
		new_baudrate = priv->baud_rate;
		if (baud_rate && baud_rate != priv->baud_rate) {
			dev_dbg(dev, "%s - baud rate is changing\n", __func__);
			retval = analyze_baud_rate(port, baud_rate);
			if (retval >= 0) {
				new_baudrate = retval;
				dev_dbg(dev, "%s - New baud rate set to %d\n",
					__func__, new_baudrate);
			}
		}
		dev_dbg(dev, "%s - baud rate is being sent as %d\n", __func__,
			new_baudrate);

		/* fill the feature_buffer with new configuration */
		put_unaligned_le32(new_baudrate, feature_buffer);
		feature_buffer[4] |= data_bits;   /* assign data bits in 2 bit space ( max 3 ) */
		/* 1 bit gap */
		feature_buffer[4] |= (stop_bits << 3);   /* assign stop bits in 1 bit space */
		feature_buffer[4] |= (parity_enable << 4);   /* assign parity flag in 1 bit space */
		feature_buffer[4] |= (parity_type << 5);   /* assign parity type in 1 bit space */
		/* 1 bit gap */
		feature_buffer[4] |= (reset << 7);   /* assign reset at end of byte, 1 bit space */

		dev_dbg(dev, "%s - device is being sent this feature report:\n", __func__);
		dev_dbg(dev, "%s - %02X - %02X - %02X - %02X - %02X\n", __func__,
			feature_buffer[0], feature_buffer[1],
			feature_buffer[2], feature_buffer[3],
			feature_buffer[4]);

		do {
			retval = usb_control_msg(port->serial->dev,
					usb_sndctrlpipe(port->serial->dev, 0),
					HID_REQ_SET_REPORT,
					USB_DIR_OUT | USB_RECIP_INTERFACE | USB_TYPE_CLASS,
					0x0300, 0, feature_buffer,
					feature_len, 500);

			if (tries++ >= 3)
				break;

		} while (retval != feature_len &&
			 retval != -ENODEV);

		if (retval != feature_len) {
			dev_err(dev, "%s - failed sending serial line settings - %d\n",
				__func__, retval);
			cypress_set_dead(port);
		} else {
			spin_lock_irqsave(&priv->lock, flags);
			priv->baud_rate = new_baudrate;
			priv->current_config = feature_buffer[4];
			spin_unlock_irqrestore(&priv->lock, flags);
			/* If we asked for a speed change encode it */
			if (baud_rate)
				tty_encode_baud_rate(tty,
					new_baudrate, new_baudrate);
		}
	break;
	case CYPRESS_GET_CONFIG:
		if (priv->get_cfg_unsafe) {
			/* Not implemented for this device,
			   and if we try to do it we're likely
			   to crash the hardware. */
			retval = -ENOTTY;
			goto out;
		}
		dev_dbg(dev, "%s - retreiving serial line settings\n", __func__);
		do {
			retval = usb_control_msg(port->serial->dev,
					usb_rcvctrlpipe(port->serial->dev, 0),
					HID_REQ_GET_REPORT,
					USB_DIR_IN | USB_RECIP_INTERFACE | USB_TYPE_CLASS,
					0x0300, 0, feature_buffer,
					feature_len, 500);

			if (tries++ >= 3)
				break;
		} while (retval != feature_len
						&& retval != -ENODEV);

		if (retval != feature_len) {
			dev_err(dev, "%s - failed to retrieve serial line settings - %d\n",
				__func__, retval);
			cypress_set_dead(port);
			goto out;
		} else {
			spin_lock_irqsave(&priv->lock, flags);
			/* store the config in one byte, and later
			   use bit masks to check values */
			priv->current_config = feature_buffer[4];
			priv->baud_rate = get_unaligned_le32(feature_buffer);
			spin_unlock_irqrestore(&priv->lock, flags);
		}
	}
	spin_lock_irqsave(&priv->lock, flags);
	++priv->cmd_count;
	spin_unlock_irqrestore(&priv->lock, flags);
out:
	kfree(feature_buffer);
	return retval;
} /* cypress_serial_control */
