static int validate_event(struct perf_event *event)
{
	struct cpu_hw_events *fake_cpuc;
	struct event_constraint *c;
	int ret = 0;

	fake_cpuc = kmalloc(sizeof(*fake_cpuc), GFP_KERNEL | __GFP_ZERO);
	if (!fake_cpuc)
		return -ENOMEM;

	c = x86_pmu.get_event_constraints(fake_cpuc, event);

	if (!c || !c->weight)
		ret = -ENOSPC;

	if (x86_pmu.put_event_constraints)
		x86_pmu.put_event_constraints(fake_cpuc, event);

	kfree(fake_cpuc);

	return ret;
}
