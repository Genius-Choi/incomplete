static u8 airo_dbm_to_pct (tdsRssiEntry *rssi_rid, u8 dbm)
{
	int i;

	if (!rssi_rid)
		return 0;

	for (i = 0; i < 256; i++)
		if (rssi_rid[i].rssidBm == dbm)
			return rssi_rid[i].rssipct;

	return 0;
}
