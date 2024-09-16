void hns_ppe_get_stats(struct hns_ppe_cb *ppe_cb, u64 *data)
{
	u64 *regs_buff = data;
	struct hns_ppe_hw_stats *hw_stats = &ppe_cb->hw_stats;

	regs_buff[0] = hw_stats->rx_pkts_from_sw;
	regs_buff[1] = hw_stats->rx_pkts;
	regs_buff[2] = hw_stats->rx_drop_no_bd;
	regs_buff[3] = hw_stats->rx_alloc_buf_fail;
	regs_buff[4] = hw_stats->rx_alloc_buf_wait;
	regs_buff[5] = hw_stats->rx_drop_no_buf;
	regs_buff[6] = hw_stats->rx_err_fifo_full;

	regs_buff[7] = hw_stats->tx_bd_form_rcb;
	regs_buff[8] = hw_stats->tx_pkts_from_rcb;
	regs_buff[9] = hw_stats->tx_pkts;
	regs_buff[10] = hw_stats->tx_err_fifo_empty;
	regs_buff[11] = hw_stats->tx_err_checksum;
}
