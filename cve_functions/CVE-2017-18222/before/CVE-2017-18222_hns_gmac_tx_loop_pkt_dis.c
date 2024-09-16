static void hns_gmac_tx_loop_pkt_dis(void *mac_drv)
{
	u32 tx_loop_pkt_pri;
	struct mac_driver *drv = (struct mac_driver *)mac_drv;

	tx_loop_pkt_pri = dsaf_read_dev(drv, GMAC_TX_LOOP_PKT_PRI_REG);
	dsaf_set_bit(tx_loop_pkt_pri, GMAC_TX_LOOP_PKT_EN_B, 1);
	dsaf_set_bit(tx_loop_pkt_pri, GMAC_TX_LOOP_PKT_HIG_PRI_B, 0);
	dsaf_write_dev(drv, GMAC_TX_LOOP_PKT_PRI_REG, tx_loop_pkt_pri);
}
