trap_handler(__attribute__((unused)) vector_t *strvec)
{
	global_data->enable_traps = true;
}
