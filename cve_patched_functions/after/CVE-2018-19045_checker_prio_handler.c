checker_prio_handler(vector_t *strvec)
{
	global_data->checker_process_priority = get_priority(strvec, "checker");
}
