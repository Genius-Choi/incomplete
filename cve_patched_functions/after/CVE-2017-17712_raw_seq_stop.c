void raw_seq_stop(struct seq_file *seq, void *v)
{
	struct raw_iter_state *state = raw_seq_private(seq);

	read_unlock(&state->h->lock);
}
