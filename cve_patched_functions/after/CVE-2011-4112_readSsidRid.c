static int readSsidRid(struct airo_info*ai, SsidRid *ssidr)
{
	return PC4500_readrid(ai, RID_SSID, ssidr, sizeof(*ssidr), 1);
}
