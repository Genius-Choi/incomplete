static int cypress_write_room(struct tty_struct *tty)
{
	struct usb_serial_port *port = tty->driver_data;
	struct cypress_private *priv = usb_get_serial_port_data(port);
	int room = 0;
	unsigned long flags;

	spin_lock_irqsave(&priv->lock, flags);
	room = kfifo_avail(&priv->write_fifo);
	spin_unlock_irqrestore(&priv->lock, flags);

	dev_dbg(&port->dev, "%s - returns %d\n", __func__, room);
	return room;
}
