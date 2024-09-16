bool trace_clock_in_ns(struct trace_array *tr)
{
	if (trace_clocks[tr->clock_id].in_ns)
		return true;

	return false;
}
