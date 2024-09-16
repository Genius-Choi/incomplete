static void perf_sysexit_disable(struct ftrace_event_call *call)
{
	int num;

	num = ((struct syscall_metadata *)call->data)->syscall_nr;

	mutex_lock(&syscall_trace_lock);
	sys_perf_refcount_exit--;
	clear_bit(num, enabled_perf_exit_syscalls);
	if (!sys_perf_refcount_exit)
		unregister_trace_sys_exit(perf_syscall_exit, NULL);
	mutex_unlock(&syscall_trace_lock);
}
