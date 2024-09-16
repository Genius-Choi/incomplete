ftrace_global_list_func(unsigned long ip, unsigned long parent_ip,
			struct ftrace_ops *op, struct pt_regs *regs)
{
	int bit;

	bit = trace_test_and_set_recursion(TRACE_GLOBAL_START, TRACE_GLOBAL_MAX);
	if (bit < 0)
		return;

	do_for_each_ftrace_op(op, ftrace_global_list) {
		op->func(ip, parent_ip, op, regs);
	} while_for_each_ftrace_op(op);

	trace_clear_recursion(bit);
}
