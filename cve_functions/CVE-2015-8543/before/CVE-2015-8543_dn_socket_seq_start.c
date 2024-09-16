static void *dn_socket_seq_start(struct seq_file *seq, loff_t *pos)
{
	return *pos ? dn_socket_get_idx(seq, *pos - 1) : SEQ_START_TOKEN;
}
