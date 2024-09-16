static void nlmclnt_locks_init_private(struct file_lock *fl, struct nlm_host *host)
{
	BUG_ON(fl->fl_ops != NULL);
	fl->fl_u.nfs_fl.state = 0;
	fl->fl_u.nfs_fl.owner = nlm_find_lockowner(host, fl->fl_owner);
	INIT_LIST_HEAD(&fl->fl_u.nfs_fl.list);
	fl->fl_ops = &nlmclnt_lock_ops;
}
