static int perf_tp_filter_match(struct perf_event *event,
				struct perf_sample_data *data)
{
	void *record = data->raw->data;

	if (likely(!event->filter) || filter_match_preds(event->filter, record))
		return 1;
	return 0;
}
