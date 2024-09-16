static int set_wep_key(struct airo_info *ai, u16 index, const char *key,
		       u16 keylen, int perm, int lock)
{
	static const unsigned char macaddr[ETH_ALEN] = { 0x01, 0, 0, 0, 0, 0 };
	WepKeyRid wkr;
	int rc;

	if (WARN_ON(keylen == 0))
		return -1;

	memset(&wkr, 0, sizeof(wkr));
	wkr.len = cpu_to_le16(sizeof(wkr));
	wkr.kindex = cpu_to_le16(index);
	wkr.klen = cpu_to_le16(keylen);
	memcpy(wkr.key, key, keylen);
	memcpy(wkr.mac, macaddr, ETH_ALEN);

	if (perm) disable_MAC(ai, lock);
	rc = writeWepKeyRid(ai, &wkr, perm, lock);
	if (perm) enable_MAC(ai, lock);
	return rc;
}
