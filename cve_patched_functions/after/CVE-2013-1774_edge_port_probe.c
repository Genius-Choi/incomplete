static int edge_port_probe(struct usb_serial_port *port)
{
	struct edgeport_port *edge_port;
	int ret;

	edge_port = kzalloc(sizeof(*edge_port), GFP_KERNEL);
	if (!edge_port)
		return -ENOMEM;

	ret = kfifo_alloc(&edge_port->write_fifo, EDGE_OUT_BUF_SIZE,
								GFP_KERNEL);
	if (ret) {
		kfree(edge_port);
		return -ENOMEM;
	}

	spin_lock_init(&edge_port->ep_lock);
	edge_port->port = port;
	edge_port->edge_serial = usb_get_serial_data(port->serial);
	edge_port->bUartMode = default_uart_mode;

	usb_set_serial_port_data(port, edge_port);

	ret = edge_create_sysfs_attrs(port);
	if (ret) {
		kfifo_free(&edge_port->write_fifo);
		kfree(edge_port);
		return ret;
	}

	return 0;
}
