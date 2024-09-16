void *raw_seq_start(struct seq_file *seq, loff_t *pos)
{
	struct raw_iter_state *state = raw_seq_private(seq);

	read_lock(&state->h->lock);
	return *pos ? raw_get_idx(seq, *pos - 1) : SEQ_START_TOKEN;
}
