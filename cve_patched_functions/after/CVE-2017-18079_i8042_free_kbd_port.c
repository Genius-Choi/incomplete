static void __init i8042_free_kbd_port(void)
{
	kfree(i8042_ports[I8042_KBD_PORT_NO].serio);
	i8042_ports[I8042_KBD_PORT_NO].serio = NULL;
}
