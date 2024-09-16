void *raw_seq_next(struct seq_file *seq, void *v, loff_t *pos)
{
	struct sock *sk;

	if (v == SEQ_START_TOKEN)
		sk = raw_get_first(seq);
	else
		sk = raw_get_next(seq, v);
	++*pos;
	return sk;
}
