atusb_set_frame_retries(struct ieee802154_hw *hw, s8 retries)
{
	struct atusb *atusb = hw->priv;
	struct device *dev = &atusb->usb_dev->dev;

	if (atusb->fw_ver_maj == 0 && atusb->fw_ver_min < 3) {
		dev_info(dev, "Automatic frame retransmission is only available from "
			"firmware version 0.3. Please update if you want this feature.");
		return -EINVAL;
	}

	return atusb_write_subreg(atusb, SR_MAX_FRAME_RETRIES, retries);
}
