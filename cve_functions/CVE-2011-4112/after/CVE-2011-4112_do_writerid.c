static int do_writerid( struct airo_info *ai, u16 rid, const void *rid_data,
			int len, int dummy ) {
	int rc;

	disable_MAC(ai, 1);
	rc = PC4500_writerid(ai, rid, rid_data, len, 1);
	enable_MAC(ai, 1);
	return rc;
}
