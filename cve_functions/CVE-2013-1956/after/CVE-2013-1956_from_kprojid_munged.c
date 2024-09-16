projid_t from_kprojid_munged(struct user_namespace *targ, kprojid_t kprojid)
{
	projid_t projid;
	projid = from_kprojid(targ, kprojid);

	if (projid == (projid_t) -1)
		projid = OVERFLOW_PROJID;
	return projid;
}
