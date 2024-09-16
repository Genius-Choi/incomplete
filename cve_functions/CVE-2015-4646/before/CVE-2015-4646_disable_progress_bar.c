void disable_progress_bar()
{
	pthread_mutex_lock(&screen_mutex);
	if(progress_enabled) {
		progress_bar(sym_count + dev_count + fifo_count + cur_blocks,
			total_inodes - total_files + total_blocks, columns);
		printf("\n");
	}
	progress_enabled = FALSE;
	pthread_mutex_unlock(&screen_mutex);
}
