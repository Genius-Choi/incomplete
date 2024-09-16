static int readStatusRid(struct airo_info *ai, StatusRid *statr, int lock)
{
	return PC4500_readrid(ai, RID_STATUS, statr, sizeof(*statr), lock);
}
