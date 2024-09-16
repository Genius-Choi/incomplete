static int writeSsidRid(struct airo_info*ai, SsidRid *pssidr, int lock)
{
	return PC4500_writerid(ai, RID_SSID, pssidr, sizeof(*pssidr), lock);
}
