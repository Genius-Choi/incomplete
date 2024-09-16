intel_get_event_constraints(struct cpu_hw_events *cpuc, struct perf_event *event)
{
	struct event_constraint *c;

	c = intel_bts_constraints(event);
	if (c)
		return c;

	c = intel_pebs_constraints(event);
	if (c)
		return c;

	c = intel_shared_regs_constraints(cpuc, event);
	if (c)
		return c;

	return x86_get_event_constraints(cpuc, event);
}
