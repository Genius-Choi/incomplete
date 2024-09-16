perf_callchain_kernel(struct perf_callchain_entry *entry, struct pt_regs *regs)
{
	if (perf_guest_cbs && perf_guest_cbs->is_in_guest()) {
		/* TODO: We don't support guest os callchain now */
		return;
	}

	perf_callchain_store(entry, regs->ip);

	dump_trace(NULL, regs, NULL, &backtrace_ops, entry);
}
