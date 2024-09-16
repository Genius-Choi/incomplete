free_seq(void *s)
{
	seq_t *seq = s;

	FREE(seq->var);
	FREE(seq->text);
	FREE(seq);
}
