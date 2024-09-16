static void *rt_cache_seq_start(struct seq_file *seq, loff_t *pos)
{
	if (*pos)
		return NULL;
	return SEQ_START_TOKEN;
}
