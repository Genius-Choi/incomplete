static void perf_event__header_size(struct perf_event *event)
{
	struct perf_sample_data *data;
	u64 sample_type = event->attr.sample_type;
	u16 size = 0;

	perf_event__read_size(event);

	if (sample_type & PERF_SAMPLE_IP)
		size += sizeof(data->ip);

	if (sample_type & PERF_SAMPLE_ADDR)
		size += sizeof(data->addr);

	if (sample_type & PERF_SAMPLE_PERIOD)
		size += sizeof(data->period);

	if (sample_type & PERF_SAMPLE_WEIGHT)
		size += sizeof(data->weight);

	if (sample_type & PERF_SAMPLE_READ)
		size += event->read_size;

	if (sample_type & PERF_SAMPLE_DATA_SRC)
		size += sizeof(data->data_src.val);

	if (sample_type & PERF_SAMPLE_TRANSACTION)
		size += sizeof(data->txn);

	event->header_size = size;
}
