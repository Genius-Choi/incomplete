static void cleanup_threaded_search(void)
{
	set_try_to_free_routine(old_try_to_free_routine);
	pthread_cond_destroy(&progress_cond);
	pthread_mutex_destroy(&read_mutex);
	pthread_mutex_destroy(&cache_mutex);
	pthread_mutex_destroy(&progress_mutex);
}
