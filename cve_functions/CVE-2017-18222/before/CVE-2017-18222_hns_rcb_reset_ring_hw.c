void hns_rcb_reset_ring_hw(struct hnae_queue *q)
{
	u32 wait_cnt;
	u32 try_cnt = 0;
	u32 could_ret;

	u32 tx_fbd_num;

	while (try_cnt++ < RCB_RESET_TRY_TIMES) {
		usleep_range(100, 200);
		tx_fbd_num = dsaf_read_dev(q, RCB_RING_TX_RING_FBDNUM_REG);
		if (tx_fbd_num)
			continue;

		dsaf_write_dev(q, RCB_RING_PREFETCH_EN_REG, 0);

		dsaf_write_dev(q, RCB_RING_T0_BE_RST, 1);

		msleep(20);
		could_ret = dsaf_read_dev(q, RCB_RING_COULD_BE_RST);

		wait_cnt = 0;
		while (!could_ret && (wait_cnt < RCB_RESET_WAIT_TIMES)) {
			dsaf_write_dev(q, RCB_RING_T0_BE_RST, 0);

			dsaf_write_dev(q, RCB_RING_T0_BE_RST, 1);

			msleep(20);
			could_ret = dsaf_read_dev(q, RCB_RING_COULD_BE_RST);

			wait_cnt++;
		}

		dsaf_write_dev(q, RCB_RING_T0_BE_RST, 0);

		if (could_ret)
			break;
	}

	if (try_cnt >= RCB_RESET_TRY_TIMES)
		dev_err(q->dev->dev, "port%d reset ring fail\n",
			hns_ae_get_vf_cb(q->handle)->port_index);
}
