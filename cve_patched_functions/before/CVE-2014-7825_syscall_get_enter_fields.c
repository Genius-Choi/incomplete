syscall_get_enter_fields(struct ftrace_event_call *call)
{
	struct syscall_metadata *entry = call->data;

	return &entry->enter_fields;
}
