static void *tcp_seek_last_pos(struct seq_file *seq)
{
	struct tcp_iter_state *st = seq->private;
	int offset = st->offset;
	int orig_num = st->num;
	void *rc = NULL;

	switch (st->state) {
	case TCP_SEQ_STATE_LISTENING:
		if (st->bucket >= INET_LHTABLE_SIZE)
			break;
		st->state = TCP_SEQ_STATE_LISTENING;
		rc = listening_get_next(seq, NULL);
		while (offset-- && rc)
			rc = listening_get_next(seq, rc);
		if (rc)
			break;
		st->bucket = 0;
		st->state = TCP_SEQ_STATE_ESTABLISHED;
		/* Fallthrough */
	case TCP_SEQ_STATE_ESTABLISHED:
		if (st->bucket > tcp_hashinfo.ehash_mask)
			break;
		rc = established_get_first(seq);
		while (offset-- && rc)
			rc = established_get_next(seq, rc);
	}

	st->num = orig_num;

	return rc;
}
