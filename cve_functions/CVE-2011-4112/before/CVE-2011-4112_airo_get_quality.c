static int airo_get_quality (StatusRid *status_rid, CapabilityRid *cap_rid)
{
	int quality = 0;
	u16 sq;

	if ((status_rid->mode & cpu_to_le16(0x3f)) != cpu_to_le16(0x3f))
		return 0;

	if (!(cap_rid->hardCap & cpu_to_le16(8)))
		return 0;

	sq = le16_to_cpu(status_rid->signalQuality);
	if (memcmp(cap_rid->prodName, "350", 3))
		if (sq > 0x20)
			quality = 0;
		else
			quality = 0x20 - sq;
	else
		if (sq > 0xb0)
			quality = 0;
		else if (sq < 0x10)
			quality = 0xa0;
		else
			quality = 0xb0 - sq;
	return quality;
}
