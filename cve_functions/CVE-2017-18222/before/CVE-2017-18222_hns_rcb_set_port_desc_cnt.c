static void hns_rcb_set_port_desc_cnt(struct rcb_common_cb *rcb_common,
				      u32 port_idx, u32 desc_cnt)
{
	dsaf_write_dev(rcb_common, RCB_CFG_BD_NUM_REG + port_idx * 4,
		       desc_cnt);
}
