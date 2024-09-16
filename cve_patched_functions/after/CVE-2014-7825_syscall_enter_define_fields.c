static int __init syscall_enter_define_fields(struct ftrace_event_call *call)
{
	struct syscall_trace_enter trace;
	struct syscall_metadata *meta = call->data;
	int ret;
	int i;
	int offset = offsetof(typeof(trace), args);

	ret = trace_define_field(call, SYSCALL_FIELD(int, nr), FILTER_OTHER);
	if (ret)
		return ret;

	for (i = 0; i < meta->nb_args; i++) {
		ret = trace_define_field(call, meta->types[i],
					 meta->args[i], offset,
					 sizeof(unsigned long), 0,
					 FILTER_OTHER);
		offset += sizeof(unsigned long);
	}

	return ret;
}
