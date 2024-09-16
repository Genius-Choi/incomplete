nlmsvc_owner_key(struct file_lock *fl)
{
	return (unsigned long)fl->fl_owner ^ (unsigned long)fl->fl_pid;
}
