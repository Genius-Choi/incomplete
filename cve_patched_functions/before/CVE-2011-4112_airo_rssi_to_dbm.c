static u8 airo_rssi_to_dbm (tdsRssiEntry *rssi_rid, u8 rssi)
{
	if (!rssi_rid)
		return 0;

	return (0x100 - rssi_rid[rssi].rssidBm);
}
