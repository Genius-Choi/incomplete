void enable_mem_log_termination(void)
{
	atexit(keepalived_free_final);
}
