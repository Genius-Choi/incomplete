static void *rose_info_next(struct seq_file *seq, void *v, loff_t *pos)
{
	return seq_hlist_next(v, &rose_list, pos);
}
