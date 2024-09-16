checker_rt_priority_handler(vector_t *strvec)
{
	int priority = get_realtime_priority(strvec, "checker");

	if (priority >= 0)
		global_data->checker_realtime_priority = priority;
}
