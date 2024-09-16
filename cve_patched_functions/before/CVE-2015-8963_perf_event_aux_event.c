void perf_event_aux_event(struct perf_event *event, unsigned long head,
			  unsigned long size, u64 flags)
{
	struct perf_output_handle handle;
	struct perf_sample_data sample;
	struct perf_aux_event {
		struct perf_event_header	header;
		u64				offset;
		u64				size;
		u64				flags;
	} rec = {
		.header = {
			.type = PERF_RECORD_AUX,
			.misc = 0,
			.size = sizeof(rec),
		},
		.offset		= head,
		.size		= size,
		.flags		= flags,
	};
	int ret;

	perf_event_header__init_id(&rec.header, &sample, event);
	ret = perf_output_begin(&handle, event, rec.header.size);

	if (ret)
		return;

	perf_output_put(&handle, rec);
	perf_event__output_id_sample(event, &handle, &sample);

	perf_output_end(&handle);
}
