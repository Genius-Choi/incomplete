static void hns_xgmac_get_stats(void *mac_drv, u64 *data)
{
	u32 i;
	u64 *buf = data;
	struct mac_driver *drv = (struct mac_driver *)mac_drv;
	struct mac_hw_stats *hw_stats = NULL;

	hw_stats = &drv->mac_cb->hw_stats;

	for (i = 0; i < ARRAY_SIZE(g_xgmac_stats_string); i++) {
		buf[i] = DSAF_STATS_READ(hw_stats,
			g_xgmac_stats_string[i].offset);
	}
}
