checker_rt_rlimit_handler(vector_t *strvec)
{
	global_data->checker_rlimit_rt = get_rt_rlimit(strvec, "checker");
}
