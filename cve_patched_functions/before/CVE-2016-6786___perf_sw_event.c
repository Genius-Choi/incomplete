void __perf_sw_event(u32 event_id, u64 nr, struct pt_regs *regs, u64 addr)
{
	int rctx;

	preempt_disable_notrace();
	rctx = perf_swevent_get_recursion_context();
	if (unlikely(rctx < 0))
		goto fail;

	___perf_sw_event(event_id, nr, regs, addr);

	perf_swevent_put_recursion_context(rctx);
fail:
	preempt_enable_notrace();
}
