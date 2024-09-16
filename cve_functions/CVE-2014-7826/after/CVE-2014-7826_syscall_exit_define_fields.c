static int __init syscall_exit_define_fields(struct ftrace_event_call *call)
{
	struct syscall_trace_exit trace;
	int ret;

	ret = trace_define_field(call, SYSCALL_FIELD(int, nr), FILTER_OTHER);
	if (ret)
		return ret;

	ret = trace_define_field(call, SYSCALL_FIELD(long, ret),
				 FILTER_OTHER);

	return ret;
}
