static struct file_lock *nfs4_alloc_init_lease(struct nfs4_file *fp, int flag)
{
	struct file_lock *fl;

	fl = locks_alloc_lock();
	if (!fl)
		return NULL;
	fl->fl_lmops = &nfsd_lease_mng_ops;
	fl->fl_flags = FL_DELEG;
	fl->fl_type = flag == NFS4_OPEN_DELEGATE_READ? F_RDLCK: F_WRLCK;
	fl->fl_end = OFFSET_MAX;
	fl->fl_owner = (fl_owner_t)fp;
	fl->fl_pid = current->tgid;
	return fl;
}
