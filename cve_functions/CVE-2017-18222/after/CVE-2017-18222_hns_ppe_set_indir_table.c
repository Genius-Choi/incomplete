void hns_ppe_set_indir_table(struct hns_ppe_cb *ppe_cb,
			     const u32 rss_tab[HNS_PPEV2_RSS_IND_TBL_SIZE])
{
	int i;
	int reg_value;

	for (i = 0; i < (HNS_PPEV2_RSS_IND_TBL_SIZE / 4); i++) {
		reg_value = dsaf_read_dev(ppe_cb,
					  PPEV2_INDRECTION_TBL_REG + i * 0x4);

		dsaf_set_field(reg_value, PPEV2_CFG_RSS_TBL_4N0_M,
			       PPEV2_CFG_RSS_TBL_4N0_S,
			       rss_tab[i * 4 + 0] & 0x1F);
		dsaf_set_field(reg_value, PPEV2_CFG_RSS_TBL_4N1_M,
			       PPEV2_CFG_RSS_TBL_4N1_S,
				rss_tab[i * 4 + 1] & 0x1F);
		dsaf_set_field(reg_value, PPEV2_CFG_RSS_TBL_4N2_M,
			       PPEV2_CFG_RSS_TBL_4N2_S,
				rss_tab[i * 4 + 2] & 0x1F);
		dsaf_set_field(reg_value, PPEV2_CFG_RSS_TBL_4N3_M,
			       PPEV2_CFG_RSS_TBL_4N3_S,
				rss_tab[i * 4 + 3] & 0x1F);
		dsaf_write_dev(
			ppe_cb, PPEV2_INDRECTION_TBL_REG + i * 0x4, reg_value);
	}
}
