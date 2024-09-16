static void nlmclnt_setlockargs(struct nlm_rqst *req, struct file_lock *fl)
{
	struct nlm_args	*argp = &req->a_args;
	struct nlm_lock	*lock = &argp->lock;

	nlmclnt_next_cookie(&argp->cookie);
	memcpy(&lock->fh, NFS_FH(fl->fl_file->f_path.dentry->d_inode), sizeof(struct nfs_fh));
	lock->caller  = utsname()->nodename;
	lock->oh.data = req->a_owner;
	lock->oh.len  = snprintf(req->a_owner, sizeof(req->a_owner), "%u@%s",
				(unsigned int)fl->fl_u.nfs_fl.owner->pid,
				utsname()->nodename);
	lock->svid = fl->fl_u.nfs_fl.owner->pid;
	lock->fl.fl_start = fl->fl_start;
	lock->fl.fl_end = fl->fl_end;
	lock->fl.fl_type = fl->fl_type;
}
