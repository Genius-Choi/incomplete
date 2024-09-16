static long get_nr_files(void)
{
	return percpu_counter_read_positive(&nr_files);
}
