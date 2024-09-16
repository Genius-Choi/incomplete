static void ctx_sched_out(struct perf_event_context *ctx,
			  struct perf_cpu_context *cpuctx,
			  enum event_type_t event_type)
{
	struct perf_event *event;
	int is_active = ctx->is_active;

	ctx->is_active &= ~event_type;
	if (likely(!ctx->nr_events))
		return;

	update_context_time(ctx);
	update_cgrp_time_from_cpuctx(cpuctx);
	if (!ctx->nr_active)
		return;

	perf_pmu_disable(ctx->pmu);
	if ((is_active & EVENT_PINNED) && (event_type & EVENT_PINNED)) {
		list_for_each_entry(event, &ctx->pinned_groups, group_entry)
			group_sched_out(event, cpuctx, ctx);
	}

	if ((is_active & EVENT_FLEXIBLE) && (event_type & EVENT_FLEXIBLE)) {
		list_for_each_entry(event, &ctx->flexible_groups, group_entry)
			group_sched_out(event, cpuctx, ctx);
	}
	perf_pmu_enable(ctx->pmu);
}
