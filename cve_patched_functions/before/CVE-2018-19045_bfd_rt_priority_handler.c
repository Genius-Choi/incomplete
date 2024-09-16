bfd_rt_priority_handler(vector_t *strvec)
{
	int priority = get_realtime_priority(strvec, "BFD");

	if (priority >= 0)
		global_data->bfd_realtime_priority = priority;
}
