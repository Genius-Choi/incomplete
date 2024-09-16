static void hns_xgmac_rx_enable(struct mac_driver *drv, u32 value)
{
	dsaf_set_dev_bit(drv, XGMAC_MAC_ENABLE_REG, XGMAC_ENABLE_RX_B, !!value);
}
