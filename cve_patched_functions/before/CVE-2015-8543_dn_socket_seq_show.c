static int dn_socket_seq_show(struct seq_file *seq, void *v)
{
	if (v == SEQ_START_TOKEN) {
		seq_puts(seq, "Local                                              Remote\n");
	} else {
		dn_socket_format_entry(seq, v);
	}
	return 0;
}
