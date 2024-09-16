init_tracer_tracefs(struct trace_array *tr, struct dentry *d_tracer)
{
	struct trace_event_file *file;
	int cpu;

	trace_create_file("available_tracers", 0444, d_tracer,
			tr, &show_traces_fops);

	trace_create_file("current_tracer", 0644, d_tracer,
			tr, &set_tracer_fops);

	trace_create_file("tracing_cpumask", 0644, d_tracer,
			  tr, &tracing_cpumask_fops);

	trace_create_file("trace_options", 0644, d_tracer,
			  tr, &tracing_iter_fops);

	trace_create_file("trace", 0644, d_tracer,
			  tr, &tracing_fops);

	trace_create_file("trace_pipe", 0444, d_tracer,
			  tr, &tracing_pipe_fops);

	trace_create_file("buffer_size_kb", 0644, d_tracer,
			  tr, &tracing_entries_fops);

	trace_create_file("buffer_total_size_kb", 0444, d_tracer,
			  tr, &tracing_total_entries_fops);

	trace_create_file("free_buffer", 0200, d_tracer,
			  tr, &tracing_free_buffer_fops);

	trace_create_file("trace_marker", 0220, d_tracer,
			  tr, &tracing_mark_fops);

	file = __find_event_file(tr, "ftrace", "print");
	if (file && file->dir)
		trace_create_file("trigger", 0644, file->dir, file,
				  &event_trigger_fops);
	tr->trace_marker_file = file;

	trace_create_file("trace_marker_raw", 0220, d_tracer,
			  tr, &tracing_mark_raw_fops);

	trace_create_file("trace_clock", 0644, d_tracer, tr,
			  &trace_clock_fops);

	trace_create_file("tracing_on", 0644, d_tracer,
			  tr, &rb_simple_fops);

	trace_create_file("timestamp_mode", 0444, d_tracer, tr,
			  &trace_time_stamp_mode_fops);

	tr->buffer_percent = 50;

	trace_create_file("buffer_percent", 0444, d_tracer,
			tr, &buffer_percent_fops);

	create_trace_options_dir(tr);

#if defined(CONFIG_TRACER_MAX_TRACE) || defined(CONFIG_HWLAT_TRACER)
	trace_create_file("tracing_max_latency", 0644, d_tracer,
			&tr->max_latency, &tracing_max_lat_fops);
#endif

	if (ftrace_create_function_files(tr, d_tracer))
		WARN(1, "Could not allocate function filter files");

#ifdef CONFIG_TRACER_SNAPSHOT
	trace_create_file("snapshot", 0644, d_tracer,
			  tr, &snapshot_fops);
#endif

	for_each_tracing_cpu(cpu)
		tracing_init_tracefs_percpu(tr, cpu);

	ftrace_init_tracefs(tr, d_tracer);
}
