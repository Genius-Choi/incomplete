static void perf_event__id_header_size(struct perf_event *event)
{
	struct perf_sample_data *data;
	u64 sample_type = event->attr.sample_type;
	u16 size = 0;

	if (sample_type & PERF_SAMPLE_TID)
		size += sizeof(data->tid_entry);

	if (sample_type & PERF_SAMPLE_TIME)
		size += sizeof(data->time);

	if (sample_type & PERF_SAMPLE_IDENTIFIER)
		size += sizeof(data->id);

	if (sample_type & PERF_SAMPLE_ID)
		size += sizeof(data->id);

	if (sample_type & PERF_SAMPLE_STREAM_ID)
		size += sizeof(data->stream_id);

	if (sample_type & PERF_SAMPLE_CPU)
		size += sizeof(data->cpu_entry);

	event->id_header_size = size;
}
