static int atusb_get_and_show_chip(struct atusb *atusb)
{
	struct usb_device *usb_dev = atusb->usb_dev;
	uint8_t man_id_0, man_id_1, part_num, version_num;
	const char *chip;

	man_id_0 = atusb_read_reg(atusb, RG_MAN_ID_0);
	man_id_1 = atusb_read_reg(atusb, RG_MAN_ID_1);
	part_num = atusb_read_reg(atusb, RG_PART_NUM);
	version_num = atusb_read_reg(atusb, RG_VERSION_NUM);

	if (atusb->err)
		return atusb->err;

	if ((man_id_1 << 8 | man_id_0) != ATUSB_JEDEC_ATMEL) {
		dev_err(&usb_dev->dev,
			"non-Atmel transceiver xxxx%02x%02x\n",
			man_id_1, man_id_0);
		goto fail;
	}

	switch (part_num) {
	case 2:
		chip = "AT86RF230";
		break;
	case 3:
		chip = "AT86RF231";
		break;
	default:
		dev_err(&usb_dev->dev,
			"unexpected transceiver, part 0x%02x version 0x%02x\n",
			part_num, version_num);
		goto fail;
	}

	dev_info(&usb_dev->dev, "ATUSB: %s version %d\n", chip, version_num);

	return 0;

fail:
	atusb->err = -ENODEV;
	return -ENODEV;
}
