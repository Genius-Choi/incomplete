static void *xt_target_seq_next(struct seq_file *seq, void *v, loff_t *ppos)
{
	return xt_mttg_seq_next(seq, v, ppos, true);
}
