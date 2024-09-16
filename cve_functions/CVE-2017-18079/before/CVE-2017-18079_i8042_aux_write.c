static int i8042_aux_write(struct serio *serio, unsigned char c)
{
	struct i8042_port *port = serio->port_data;

	return i8042_command(&c, port->mux == -1 ?
					I8042_CMD_AUX_SEND :
					I8042_CMD_MUX_SEND + port->mux);
}
