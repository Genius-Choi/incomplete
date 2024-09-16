static int dvb_usbv2_media_device_register(struct dvb_usb_adapter *adap)
{
#ifdef CONFIG_MEDIA_CONTROLLER_DVB
	return media_device_register(adap->dvb_adap.mdev);
#else
	return 0;
#endif
}
