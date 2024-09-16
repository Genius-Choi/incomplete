static int context_equiv(struct perf_event_context *ctx1,
			 struct perf_event_context *ctx2)
{
	return ctx1->parent_ctx && ctx1->parent_ctx == ctx2->parent_ctx
		&& ctx1->parent_gen == ctx2->parent_gen
		&& !ctx1->pin_count && !ctx2->pin_count;
}
