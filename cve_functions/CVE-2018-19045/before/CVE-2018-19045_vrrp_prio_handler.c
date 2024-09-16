vrrp_prio_handler(vector_t *strvec)
{
	global_data->vrrp_process_priority = get_priority(strvec, "vrrp");
}
