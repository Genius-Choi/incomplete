static int perf_sysexit_enable(struct ftrace_event_call *call)
{
	int ret = 0;
	int num;

	num = ((struct syscall_metadata *)call->data)->syscall_nr;

	mutex_lock(&syscall_trace_lock);
	if (!sys_perf_refcount_exit)
		ret = register_trace_sys_exit(perf_syscall_exit, NULL);
	if (ret) {
		pr_info("event trace: Could not activate"
				"syscall exit trace point");
	} else {
		set_bit(num, enabled_perf_exit_syscalls);
		sys_perf_refcount_exit++;
	}
	mutex_unlock(&syscall_trace_lock);
	return ret;
}
