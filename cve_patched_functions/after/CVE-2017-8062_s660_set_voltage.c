static int s660_set_voltage(struct dvb_frontend *fe,
			    enum fe_sec_voltage voltage)
{
	struct dvb_usb_adapter *d =
		(struct dvb_usb_adapter *)(fe->dvb->priv);
	struct dw2102_state *st = (struct dw2102_state *)d->dev->priv;

	dw210x_set_voltage(fe, voltage);
	if (st->old_set_voltage)
		st->old_set_voltage(fe, voltage);

	return 0;
}
