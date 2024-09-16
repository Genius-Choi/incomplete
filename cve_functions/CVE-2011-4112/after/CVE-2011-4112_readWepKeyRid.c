static int readWepKeyRid(struct airo_info *ai, WepKeyRid *wkr, int temp, int lock)
{
	return PC4500_readrid(ai, temp ? RID_WEP_TEMP : RID_WEP_PERM,
				wkr, sizeof(*wkr), lock);
}
