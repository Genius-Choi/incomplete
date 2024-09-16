static void process_lock_setup_atfork(void)
{
	pthread_atfork(cgm_lock, cgm_unlock, cgm_unlock);
}
