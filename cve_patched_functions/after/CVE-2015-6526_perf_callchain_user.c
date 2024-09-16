perf_callchain_user(struct perf_callchain_entry *entry, struct pt_regs *regs)
{
	if (current_is_64bit())
		perf_callchain_user_64(entry, regs);
	else
		perf_callchain_user_32(entry, regs);
}
