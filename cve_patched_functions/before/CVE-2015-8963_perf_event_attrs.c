const struct perf_event_attr *perf_event_attrs(struct perf_event *event)
{
	if (!event)
		return ERR_PTR(-EINVAL);

	return &event->attr;
}
