static void perf_sysenter_disable(struct ftrace_event_call *call)
{
	int num;

	num = ((struct syscall_metadata *)call->data)->syscall_nr;

	mutex_lock(&syscall_trace_lock);
	sys_perf_refcount_enter--;
	clear_bit(num, enabled_perf_enter_syscalls);
	if (!sys_perf_refcount_enter)
		unregister_trace_sys_enter(perf_syscall_enter, NULL);
	mutex_unlock(&syscall_trace_lock);
}
