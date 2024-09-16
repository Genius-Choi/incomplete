static int dw3101_tuner_attach(struct dvb_usb_adapter *adap)
{
	dvb_attach(dvb_pll_attach, adap->fe_adap[0].fe, 0x60,
		&adap->dev->i2c_adap, DVB_PLL_TUA6034);

	return 0;
}
