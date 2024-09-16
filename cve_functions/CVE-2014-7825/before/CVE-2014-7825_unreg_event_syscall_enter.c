static void unreg_event_syscall_enter(struct ftrace_event_file *file,
				      struct ftrace_event_call *call)
{
	struct trace_array *tr = file->tr;
	int num;

	num = ((struct syscall_metadata *)call->data)->syscall_nr;
	if (WARN_ON_ONCE(num < 0 || num >= NR_syscalls))
		return;
	mutex_lock(&syscall_trace_lock);
	tr->sys_refcount_enter--;
	RCU_INIT_POINTER(tr->enter_syscall_files[num], NULL);
	if (!tr->sys_refcount_enter)
		unregister_trace_sys_enter(ftrace_syscall_enter, tr);
	mutex_unlock(&syscall_trace_lock);
}
