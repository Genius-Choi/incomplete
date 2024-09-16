static void hns_xgmac_pma_fec_enable(struct mac_driver *drv, u32 tx_value,
				     u32 rx_value)
{
	u32 origin = dsaf_read_dev(drv, XGMAC_PMA_FEC_CONTROL_REG);

	dsaf_set_bit(origin, XGMAC_PMA_FEC_CTL_TX_B, !!tx_value);
	dsaf_set_bit(origin, XGMAC_PMA_FEC_CTL_RX_B, !!rx_value);
	dsaf_write_dev(drv, XGMAC_PMA_FEC_CONTROL_REG, origin);
}
