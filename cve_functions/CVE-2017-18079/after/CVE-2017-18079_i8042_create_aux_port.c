static int __init i8042_create_aux_port(int idx)
{
	struct serio *serio;
	int port_no = idx < 0 ? I8042_AUX_PORT_NO : I8042_MUX_PORT_NO + idx;
	struct i8042_port *port = &i8042_ports[port_no];

	serio = kzalloc(sizeof(struct serio), GFP_KERNEL);
	if (!serio)
		return -ENOMEM;

	serio->id.type		= SERIO_8042;
	serio->write		= i8042_aux_write;
	serio->start		= i8042_start;
	serio->stop		= i8042_stop;
	serio->ps2_cmd_mutex	= &i8042_mutex;
	serio->port_data	= port;
	serio->dev.parent	= &i8042_platform_device->dev;
	if (idx < 0) {
		strlcpy(serio->name, "i8042 AUX port", sizeof(serio->name));
		strlcpy(serio->phys, I8042_AUX_PHYS_DESC, sizeof(serio->phys));
		strlcpy(serio->firmware_id, i8042_aux_firmware_id,
			sizeof(serio->firmware_id));
		serio->close = i8042_port_close;
	} else {
		snprintf(serio->name, sizeof(serio->name), "i8042 AUX%d port", idx);
		snprintf(serio->phys, sizeof(serio->phys), I8042_MUX_PHYS_DESC, idx + 1);
		strlcpy(serio->firmware_id, i8042_aux_firmware_id,
			sizeof(serio->firmware_id));
	}

	port->serio = serio;
	port->mux = idx;
	port->irq = I8042_AUX_IRQ;

	return 0;
}
