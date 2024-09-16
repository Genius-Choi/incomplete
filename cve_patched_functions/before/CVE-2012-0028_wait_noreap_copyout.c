static int wait_noreap_copyout(struct task_struct *p, pid_t pid, uid_t uid,
			       int why, int status,
			       struct siginfo __user *infop,
			       struct rusage __user *rusagep)
{
	int retval = rusagep ? getrusage(p, RUSAGE_BOTH, rusagep) : 0;

	put_task_struct(p);
	if (!retval)
		retval = put_user(SIGCHLD, &infop->si_signo);
	if (!retval)
		retval = put_user(0, &infop->si_errno);
	if (!retval)
		retval = put_user((short)why, &infop->si_code);
	if (!retval)
		retval = put_user(pid, &infop->si_pid);
	if (!retval)
		retval = put_user(uid, &infop->si_uid);
	if (!retval)
		retval = put_user(status, &infop->si_status);
	if (!retval)
		retval = pid;
	return retval;
}
