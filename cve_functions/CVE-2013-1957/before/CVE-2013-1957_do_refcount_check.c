static inline int do_refcount_check(struct mount *mnt, int count)
{
	int mycount = mnt_get_count(mnt) - mnt->mnt_ghosts;
	return (mycount > count);
}
