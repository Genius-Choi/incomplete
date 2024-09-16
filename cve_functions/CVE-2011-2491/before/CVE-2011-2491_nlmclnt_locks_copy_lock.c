static void nlmclnt_locks_copy_lock(struct file_lock *new, struct file_lock *fl)
{
	spin_lock(&fl->fl_u.nfs_fl.owner->host->h_lock);
	new->fl_u.nfs_fl.state = fl->fl_u.nfs_fl.state;
	new->fl_u.nfs_fl.owner = nlm_get_lockowner(fl->fl_u.nfs_fl.owner);
	list_add_tail(&new->fl_u.nfs_fl.list, &fl->fl_u.nfs_fl.owner->host->h_granted);
	spin_unlock(&fl->fl_u.nfs_fl.owner->host->h_lock);
}
