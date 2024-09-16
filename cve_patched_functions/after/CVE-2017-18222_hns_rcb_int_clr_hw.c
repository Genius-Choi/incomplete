void hns_rcb_int_clr_hw(struct hnae_queue *q, u32 flag)
{
	if (flag & RCB_INT_FLAG_TX) {
		dsaf_write_dev(q, RCB_RING_INTSTS_TX_RING_REG, 1);
		dsaf_write_dev(q, RCB_RING_INTSTS_TX_OVERTIME_REG, 1);
	}

	if (flag & RCB_INT_FLAG_RX) {
		dsaf_write_dev(q, RCB_RING_INTSTS_RX_RING_REG, 1);
		dsaf_write_dev(q, RCB_RING_INTSTS_RX_OVERTIME_REG, 1);
	}
}
