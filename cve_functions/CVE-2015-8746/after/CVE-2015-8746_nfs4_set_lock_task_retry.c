nfs4_set_lock_task_retry(unsigned long timeout)
{
	freezable_schedule_timeout_killable_unsafe(timeout);
	timeout <<= 1;
	if (timeout > NFS4_LOCK_MAXTIMEOUT)
		return NFS4_LOCK_MAXTIMEOUT;
	return timeout;
}
