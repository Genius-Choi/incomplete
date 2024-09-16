nfsd_change_deleg_cb(struct file_lock *onlist, int arg,
		     struct list_head *dispose)
{
	if (arg & F_UNLCK)
		return lease_modify(onlist, arg, dispose);
	else
		return -EAGAIN;
}
