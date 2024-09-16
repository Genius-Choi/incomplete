static struct sock *socket_get_idx(struct seq_file *seq, loff_t *pos)
{
	struct sock *sk = dn_socket_get_first(seq);

	if (sk) {
		while(*pos && (sk = dn_socket_get_next(seq, sk)))
			--*pos;
	}
	return *pos ? NULL : sk;
}
