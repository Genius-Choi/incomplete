static void *xt_mttg_seq_start(struct seq_file *seq, loff_t *pos,
    bool is_target)
{
	struct nf_mttg_trav *trav = seq->private;
	unsigned int j;

	trav->class = MTTG_TRAV_INIT;
	for (j = 0; j < *pos; ++j)
		if (xt_mttg_seq_next(seq, NULL, NULL, is_target) == NULL)
			return NULL;
	return trav;
}
