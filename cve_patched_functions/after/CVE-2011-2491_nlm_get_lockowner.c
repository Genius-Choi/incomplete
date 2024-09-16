static struct nlm_lockowner *nlm_get_lockowner(struct nlm_lockowner *lockowner)
{
	atomic_inc(&lockowner->count);
	return lockowner;
}
