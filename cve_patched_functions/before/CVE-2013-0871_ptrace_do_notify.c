static void ptrace_do_notify(int signr, int exit_code, int why)
{
	siginfo_t info;

	memset(&info, 0, sizeof info);
	info.si_signo = signr;
	info.si_code = exit_code;
	info.si_pid = task_pid_vnr(current);
	info.si_uid = from_kuid_munged(current_user_ns(), current_uid());

	/* Let the debugger run.  */
	ptrace_stop(exit_code, why, 1, &info);
}
