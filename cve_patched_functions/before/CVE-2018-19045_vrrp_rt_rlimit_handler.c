vrrp_rt_rlimit_handler(vector_t *strvec)
{
	global_data->vrrp_rlimit_rt = get_rt_rlimit(strvec, "vrrp");
}
