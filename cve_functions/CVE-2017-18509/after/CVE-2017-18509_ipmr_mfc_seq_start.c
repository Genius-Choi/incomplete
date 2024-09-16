static void *ipmr_mfc_seq_start(struct seq_file *seq, loff_t *pos)
{
	struct ipmr_mfc_iter *it = seq->private;
	struct net *net = seq_file_net(seq);
	struct mr6_table *mrt;

	mrt = ip6mr_get_table(net, RT6_TABLE_DFLT);
	if (!mrt)
		return ERR_PTR(-ENOENT);

	it->mrt = mrt;
	return *pos ? ipmr_mfc_seq_idx(net, seq->private, *pos - 1)
		: SEQ_START_TOKEN;
}
