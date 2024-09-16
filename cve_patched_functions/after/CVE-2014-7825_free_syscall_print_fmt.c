static void __init free_syscall_print_fmt(struct ftrace_event_call *call)
{
	struct syscall_metadata *entry = call->data;

	if (entry->enter_event == call)
		kfree(call->print_fmt);
}
