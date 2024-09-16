namespace_ipsets_handler(vector_t *strvec)
{
	if (!strvec)
		return;

	global_data->namespace_with_ipsets = true;
}
