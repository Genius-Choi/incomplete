void hns_rcb_wait_fbd_clean(struct hnae_queue **qs, int q_num, u32 flag)
{
	int i, wait_cnt;
	u32 fbd_num;

	for (wait_cnt = i = 0; i < q_num; wait_cnt++) {
		usleep_range(200, 300);
		fbd_num = 0;
		if (flag & RCB_INT_FLAG_TX)
			fbd_num += dsaf_read_dev(qs[i],
						 RCB_RING_TX_RING_FBDNUM_REG);
		if (flag & RCB_INT_FLAG_RX)
			fbd_num += dsaf_read_dev(qs[i],
						 RCB_RING_RX_RING_FBDNUM_REG);
		if (!fbd_num)
			i++;
		if (wait_cnt >= 10000)
			break;
	}

	if (i < q_num)
		dev_err(qs[i]->handle->owner_dev,
			"queue(%d) wait fbd(%d) clean fail!!\n", i, fbd_num);
}
