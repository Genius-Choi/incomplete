static int edge_ioctl(struct tty_struct *tty,
					unsigned int cmd, unsigned long arg)
{
	struct usb_serial_port *port = tty->driver_data;
	struct edgeport_port *edge_port = usb_get_serial_port_data(port);
	struct async_icount cnow;
	struct async_icount cprev;

	dev_dbg(&port->dev, "%s - port %d, cmd = 0x%x\n", __func__, port->number, cmd);

	switch (cmd) {
	case TIOCGSERIAL:
		dev_dbg(&port->dev, "%s - TIOCGSERIAL\n", __func__);
		return get_serial_info(edge_port,
				(struct serial_struct __user *) arg);
	case TIOCMIWAIT:
		dev_dbg(&port->dev, "%s - TIOCMIWAIT\n", __func__);
		cprev = edge_port->icount;
		while (1) {
			interruptible_sleep_on(&edge_port->delta_msr_wait);
			/* see if a signal did it */
			if (signal_pending(current))
				return -ERESTARTSYS;
			cnow = edge_port->icount;
			if (cnow.rng == cprev.rng && cnow.dsr == cprev.dsr &&
			    cnow.dcd == cprev.dcd && cnow.cts == cprev.cts)
				return -EIO; /* no change => error */
			if (((arg & TIOCM_RNG) && (cnow.rng != cprev.rng)) ||
			    ((arg & TIOCM_DSR) && (cnow.dsr != cprev.dsr)) ||
			    ((arg & TIOCM_CD)  && (cnow.dcd != cprev.dcd)) ||
			    ((arg & TIOCM_CTS) && (cnow.cts != cprev.cts))) {
				return 0;
			}
			cprev = cnow;
		}
		/* not reached */
		break;
	}
	return -ENOIOCTLCMD;
}
