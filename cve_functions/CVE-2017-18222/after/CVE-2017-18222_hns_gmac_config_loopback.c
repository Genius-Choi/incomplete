static int hns_gmac_config_loopback(void *mac_drv, enum hnae_loop loop_mode,
				    u8 enable)
{
	struct mac_driver *drv = (struct mac_driver *)mac_drv;

	switch (loop_mode) {
	case MAC_INTERNALLOOP_MAC:
		dsaf_set_dev_bit(drv, GMAC_LOOP_REG, GMAC_LP_REG_CF2MI_LP_EN_B,
				 !!enable);
		break;
	default:
		dev_err(drv->dev, "loop_mode error\n");
		return -EINVAL;
	}

	return 0;
}
