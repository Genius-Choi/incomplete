static int raw_seq_show(struct seq_file *seq, void *v)
{
	if (v == SEQ_START_TOKEN)
		seq_printf(seq, "  sl  local_address rem_address   st tx_queue "
				"rx_queue tr tm->when retrnsmt   uid  timeout "
				"inode ref pointer drops\n");
	else
		raw_sock_seq_show(seq, v, raw_seq_private(seq)->bucket);
	return 0;
}
