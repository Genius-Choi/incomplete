static int get_wep_tx_idx(struct airo_info *ai)
{
	WepKeyRid wkr;
	int rc;
	__le16 lastindex;

	rc = readWepKeyRid(ai, &wkr, 1, 1);
	if (rc != SUCCESS)
		return -1;
	do {
		lastindex = wkr.kindex;
		if (wkr.kindex == cpu_to_le16(0xffff))
			return wkr.mac[0];
		rc = readWepKeyRid(ai, &wkr, 0, 1);
		if (rc != SUCCESS)
			return -1;
	} while (lastindex != wkr.kindex);
	return -1;
}
