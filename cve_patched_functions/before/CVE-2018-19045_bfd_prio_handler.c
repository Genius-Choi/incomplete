bfd_prio_handler(vector_t *strvec)
{
	global_data->bfd_process_priority = get_priority(strvec, "bfd");
}
