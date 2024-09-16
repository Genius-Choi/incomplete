static int nlmsvc_same_owner(struct file_lock *fl1, struct file_lock *fl2)
{
	return fl1->fl_owner == fl2->fl_owner && fl1->fl_pid == fl2->fl_pid;
}
