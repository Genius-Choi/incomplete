static int get_wep_key(struct airo_info *ai, u16 index, char *buf, u16 buflen)
{
	WepKeyRid wkr;
	int rc;
	__le16 lastindex;

	rc = readWepKeyRid(ai, &wkr, 1, 1);
	if (rc != SUCCESS)
		return -1;
	do {
		lastindex = wkr.kindex;
		if (le16_to_cpu(wkr.kindex) == index) {
			int klen = min_t(int, buflen, le16_to_cpu(wkr.klen));
			memcpy(buf, wkr.key, klen);
			return klen;
		}
		rc = readWepKeyRid(ai, &wkr, 0, 1);
		if (rc != SUCCESS)
			return -1;
	} while (lastindex != wkr.kindex);
	return -1;
}
