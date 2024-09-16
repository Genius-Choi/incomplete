void hns_rcb_update_stats(struct hnae_queue *queue)
{
	struct ring_pair_cb *ring =
		container_of(queue, struct ring_pair_cb, q);
	struct dsaf_device *dsaf_dev = ring->rcb_common->dsaf_dev;
	struct ppe_common_cb *ppe_common
		= dsaf_dev->ppe_common[ring->rcb_common->comm_index];
	struct hns_ring_hw_stats *hw_stats = &ring->hw_stats;

	hw_stats->rx_pkts += dsaf_read_dev(queue,
			 RCB_RING_RX_RING_PKTNUM_RECORD_REG);
	dsaf_write_dev(queue, RCB_RING_RX_RING_PKTNUM_RECORD_REG, 0x1);

	hw_stats->ppe_rx_ok_pkts += dsaf_read_dev(ppe_common,
			 PPE_COM_HIS_RX_PKT_QID_OK_CNT_REG + 4 * ring->index);
	hw_stats->ppe_rx_drop_pkts += dsaf_read_dev(ppe_common,
			 PPE_COM_HIS_RX_PKT_QID_DROP_CNT_REG + 4 * ring->index);

	hw_stats->tx_pkts += dsaf_read_dev(queue,
			 RCB_RING_TX_RING_PKTNUM_RECORD_REG);
	dsaf_write_dev(queue, RCB_RING_TX_RING_PKTNUM_RECORD_REG, 0x1);

	hw_stats->ppe_tx_ok_pkts += dsaf_read_dev(ppe_common,
			 PPE_COM_HIS_TX_PKT_QID_OK_CNT_REG + 4 * ring->index);
	hw_stats->ppe_tx_drop_pkts += dsaf_read_dev(ppe_common,
			 PPE_COM_HIS_TX_PKT_QID_ERR_CNT_REG + 4 * ring->index);
}
