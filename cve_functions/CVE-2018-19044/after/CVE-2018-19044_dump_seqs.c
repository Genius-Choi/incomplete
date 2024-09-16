dump_seqs(void)
{
	seq_t *seq;
	element e;

	LIST_FOREACH(seq_list, seq, e)
		log_message(LOG_INFO, "SEQ: %s => %d -> %d step %d: '%s'", seq->var, seq->next, seq->last, seq->step, seq->text);
	log_message(LOG_INFO, "%s", "");
}
