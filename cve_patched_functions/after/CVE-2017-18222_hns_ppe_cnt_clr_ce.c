static void hns_ppe_cnt_clr_ce(struct hns_ppe_cb *ppe_cb)
{
	dsaf_set_dev_bit(ppe_cb, PPE_TNL_0_5_CNT_CLR_CE_REG,
			 PPE_CNT_CLR_CE_B, 1);
}
