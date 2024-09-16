static int readAPListRid(struct airo_info *ai, APListRid *aplr)
{
	return PC4500_readrid(ai, RID_APLIST, aplr, sizeof(*aplr), 1);
}
