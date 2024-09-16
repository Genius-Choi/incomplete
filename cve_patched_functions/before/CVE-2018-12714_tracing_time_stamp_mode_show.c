static int tracing_time_stamp_mode_show(struct seq_file *m, void *v)
{
	struct trace_array *tr = m->private;

	mutex_lock(&trace_types_lock);

	if (ring_buffer_time_stamp_abs(tr->trace_buffer.buffer))
		seq_puts(m, "delta [absolute]\n");
	else
		seq_puts(m, "[delta] absolute\n");

	mutex_unlock(&trace_types_lock);

	return 0;
}
