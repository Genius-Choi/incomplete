static int __init i8042_create_kbd_port(void)
{
	struct serio *serio;
	struct i8042_port *port = &i8042_ports[I8042_KBD_PORT_NO];

	serio = kzalloc(sizeof(struct serio), GFP_KERNEL);
	if (!serio)
		return -ENOMEM;

	serio->id.type		= i8042_direct ? SERIO_8042 : SERIO_8042_XL;
	serio->write		= i8042_dumbkbd ? NULL : i8042_kbd_write;
	serio->start		= i8042_start;
	serio->stop		= i8042_stop;
	serio->close		= i8042_port_close;
	serio->ps2_cmd_mutex	= &i8042_mutex;
	serio->port_data	= port;
	serio->dev.parent	= &i8042_platform_device->dev;
	strlcpy(serio->name, "i8042 KBD port", sizeof(serio->name));
	strlcpy(serio->phys, I8042_KBD_PHYS_DESC, sizeof(serio->phys));
	strlcpy(serio->firmware_id, i8042_kbd_firmware_id,
		sizeof(serio->firmware_id));

	port->serio = serio;
	port->irq = I8042_KBD_IRQ;

	return 0;
}
