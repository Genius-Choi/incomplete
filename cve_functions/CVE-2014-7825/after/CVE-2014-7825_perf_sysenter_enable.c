static int perf_sysenter_enable(struct ftrace_event_call *call)
{
	int ret = 0;
	int num;

	num = ((struct syscall_metadata *)call->data)->syscall_nr;

	mutex_lock(&syscall_trace_lock);
	if (!sys_perf_refcount_enter)
		ret = register_trace_sys_enter(perf_syscall_enter, NULL);
	if (ret) {
		pr_info("event trace: Could not activate"
				"syscall entry trace point");
	} else {
		set_bit(num, enabled_perf_enter_syscalls);
		sys_perf_refcount_enter++;
	}
	mutex_unlock(&syscall_trace_lock);
	return ret;
}
