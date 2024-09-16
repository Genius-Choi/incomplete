use_polling_handler(vector_t *strvec)
{
	if (!strvec)
		return;

	global_data->linkbeat_use_polling = true;
}
