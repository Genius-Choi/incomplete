static void hns_gmac_port_mode_get(void *mac_drv,
				   struct hns_gmac_port_mode_cfg *port_mode)
{
	u32 tx_ctrl;
	u32 recv_ctrl;
	struct mac_driver *drv = (struct mac_driver *)mac_drv;

	port_mode->port_mode = (enum hns_port_mode)dsaf_get_dev_field(
		drv, GMAC_PORT_MODE_REG, GMAC_PORT_MODE_M, GMAC_PORT_MODE_S);

	tx_ctrl = dsaf_read_dev(drv, GMAC_TRANSMIT_CONTROL_REG);
	recv_ctrl = dsaf_read_dev(drv, GMAC_RECV_CONTROL_REG);

	port_mode->max_frm_size =
		dsaf_get_dev_field(drv, GMAC_MAX_FRM_SIZE_REG,
				   GMAC_MAX_FRM_SIZE_M, GMAC_MAX_FRM_SIZE_S);
	port_mode->short_runts_thr =
		dsaf_get_dev_field(drv, GMAC_SHORT_RUNTS_THR_REG,
				   GMAC_SHORT_RUNTS_THR_M,
				   GMAC_SHORT_RUNTS_THR_S);

	port_mode->pad_enable = dsaf_get_bit(tx_ctrl, GMAC_TX_PAD_EN_B);
	port_mode->crc_add = dsaf_get_bit(tx_ctrl, GMAC_TX_CRC_ADD_B);
	port_mode->an_enable = dsaf_get_bit(tx_ctrl, GMAC_TX_AN_EN_B);

	port_mode->runt_pkt_en =
		dsaf_get_bit(recv_ctrl, GMAC_RECV_CTRL_RUNT_PKT_EN_B);
	port_mode->strip_pad_en =
		dsaf_get_bit(recv_ctrl, GMAC_RECV_CTRL_STRIP_PAD_EN_B);
}
