static void cypress_set_dead(struct usb_serial_port *port)
{
	struct cypress_private *priv = usb_get_serial_port_data(port);
	unsigned long flags;

	spin_lock_irqsave(&priv->lock, flags);
	if (!priv->comm_is_ok) {
		spin_unlock_irqrestore(&priv->lock, flags);
		return;
	}
	priv->comm_is_ok = 0;
	spin_unlock_irqrestore(&priv->lock, flags);

	dev_err(&port->dev, "cypress_m8 suspending failing port %d - "
		"interval might be too short\n", port->port_number);
}
