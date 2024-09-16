static int whiteheat_open(struct tty_struct *tty, struct usb_serial_port *port)
{
	int retval;

	retval = start_command_port(port->serial);
	if (retval)
		goto exit;

	/* send an open port command */
	retval = firm_open(port);
	if (retval) {
		stop_command_port(port->serial);
		goto exit;
	}

	retval = firm_purge(port, WHITEHEAT_PURGE_RX | WHITEHEAT_PURGE_TX);
	if (retval) {
		firm_close(port);
		stop_command_port(port->serial);
		goto exit;
	}

	if (tty)
		firm_setup_port(tty);

	/* Work around HCD bugs */
	usb_clear_halt(port->serial->dev, port->read_urb->pipe);
	usb_clear_halt(port->serial->dev, port->write_urb->pipe);

	retval = usb_serial_generic_open(tty, port);
	if (retval) {
		firm_close(port);
		stop_command_port(port->serial);
		goto exit;
	}
exit:
	return retval;
}
