__ftrace_ops_list_func(unsigned long ip, unsigned long parent_ip,
		       struct ftrace_ops *ignored, struct pt_regs *regs)
{
	struct ftrace_ops *op;
	int bit;

	if (function_trace_stop)
		return;

	bit = trace_test_and_set_recursion(TRACE_LIST_START, TRACE_LIST_MAX);
	if (bit < 0)
		return;

	/*
	 * Some of the ops may be dynamically allocated,
	 * they must be freed after a synchronize_sched().
	 */
	preempt_disable_notrace();
	do_for_each_ftrace_op(op, ftrace_ops_list) {
		if (ftrace_ops_test(op, ip))
			op->func(ip, parent_ip, op, regs);
	} while_for_each_ftrace_op(op);
	preempt_enable_notrace();
	trace_clear_recursion(bit);
}
