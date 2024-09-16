static int tcp4_seq_show(struct seq_file *seq, void *v)
{
	struct tcp_iter_state *st;
	int len;

	if (v == SEQ_START_TOKEN) {
		seq_printf(seq, "%-*s\n", TMPSZ - 1,
			   "  sl  local_address rem_address   st tx_queue "
			   "rx_queue tr tm->when retrnsmt   uid  timeout "
			   "inode");
		goto out;
	}
	st = seq->private;

	switch (st->state) {
	case TCP_SEQ_STATE_LISTENING:
	case TCP_SEQ_STATE_ESTABLISHED:
		get_tcp4_sock(v, seq, st->num, &len);
		break;
	case TCP_SEQ_STATE_OPENREQ:
		get_openreq4(st->syn_wait_sk, v, seq, st->num, st->uid, &len);
		break;
	case TCP_SEQ_STATE_TIME_WAIT:
		get_timewait4_sock(v, seq, st->num, &len);
		break;
	}
	seq_printf(seq, "%*s\n", TMPSZ - 1 - len, "");
out:
	return 0;
}
