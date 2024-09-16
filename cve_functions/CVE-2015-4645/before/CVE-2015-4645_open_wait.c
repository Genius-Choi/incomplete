int open_wait(char *pathname, int flags, mode_t mode)
{
	if (!open_unlimited) {
		pthread_mutex_lock(&open_mutex);
		while (open_count == 0)
			pthread_cond_wait(&open_empty, &open_mutex);
		open_count --;
		pthread_mutex_unlock(&open_mutex);
	}

	return open(pathname, flags, mode);
}
