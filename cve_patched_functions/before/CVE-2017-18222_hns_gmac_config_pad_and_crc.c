static void hns_gmac_config_pad_and_crc(void *mac_drv, u8 newval)
{
	u32 tx_ctrl;
	struct mac_driver *drv = (struct mac_driver *)mac_drv;

	tx_ctrl = dsaf_read_dev(drv, GMAC_TRANSMIT_CONTROL_REG);
	dsaf_set_bit(tx_ctrl, GMAC_TX_PAD_EN_B, !!newval);
	dsaf_set_bit(tx_ctrl, GMAC_TX_CRC_ADD_B, !!newval);
	dsaf_write_dev(drv, GMAC_TRANSMIT_CONTROL_REG, tx_ctrl);
}
