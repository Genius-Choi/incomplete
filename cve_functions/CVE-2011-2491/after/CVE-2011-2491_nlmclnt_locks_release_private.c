static void nlmclnt_locks_release_private(struct file_lock *fl)
{
	spin_lock(&fl->fl_u.nfs_fl.owner->host->h_lock);
	list_del(&fl->fl_u.nfs_fl.list);
	spin_unlock(&fl->fl_u.nfs_fl.owner->host->h_lock);
	nlm_put_lockowner(fl->fl_u.nfs_fl.owner);
}
