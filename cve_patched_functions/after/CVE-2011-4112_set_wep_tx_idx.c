static int set_wep_tx_idx(struct airo_info *ai, u16 index, int perm, int lock)
{
	WepKeyRid wkr;
	int rc;

	memset(&wkr, 0, sizeof(wkr));
	wkr.len = cpu_to_le16(sizeof(wkr));
	wkr.kindex = cpu_to_le16(0xffff);
	wkr.mac[0] = (char)index;

	if (perm) {
		ai->defindex = (char)index;
		disable_MAC(ai, lock);
	}

	rc = writeWepKeyRid(ai, &wkr, perm, lock);

	if (perm)
		enable_MAC(ai, lock);
	return rc;
}
