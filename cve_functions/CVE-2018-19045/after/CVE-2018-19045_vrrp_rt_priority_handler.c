vrrp_rt_priority_handler(vector_t *strvec)
{
	int priority = get_realtime_priority(strvec, "vrrp");

	if (priority >= 0)
		global_data->vrrp_realtime_priority = priority;
}
