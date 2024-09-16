intel_pebs_constraints(struct perf_event *event)
{
	struct event_constraint *c;

	if (!event->attr.precise_ip)
		return NULL;

	if (x86_pmu.pebs_constraints) {
		for_each_event_constraint(c, x86_pmu.pebs_constraints) {
			if ((event->hw.config & c->cmask) == c->code)
				return c;
		}
	}

	return &emptyconstraint;
}
