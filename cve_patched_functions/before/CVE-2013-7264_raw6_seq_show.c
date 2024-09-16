static int raw6_seq_show(struct seq_file *seq, void *v)
{
	if (v == SEQ_START_TOKEN) {
		seq_puts(seq, IPV6_SEQ_DGRAM_HEADER);
	} else {
		struct sock *sp = v;
		__u16 srcp  = inet_sk(sp)->inet_num;
		ip6_dgram_sock_seq_show(seq, v, srcp, 0,
					raw_seq_private(seq)->bucket);
	}
	return 0;
}
