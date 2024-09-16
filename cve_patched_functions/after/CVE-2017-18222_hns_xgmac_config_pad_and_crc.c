static void hns_xgmac_config_pad_and_crc(void *mac_drv, u8 newval)
{
	struct mac_driver *drv = (struct mac_driver *)mac_drv;
	u32 origin = dsaf_read_dev(drv, XGMAC_MAC_CONTROL_REG);

	dsaf_set_bit(origin, XGMAC_CTL_TX_PAD_B, !!newval);
	dsaf_set_bit(origin, XGMAC_CTL_TX_FCS_B, !!newval);
	dsaf_set_bit(origin, XGMAC_CTL_RX_FCS_B, !!newval);
	dsaf_write_dev(drv, XGMAC_MAC_CONTROL_REG, origin);
}
