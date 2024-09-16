static int xt_match_seq_show(struct seq_file *seq, void *v)
{
	const struct nf_mttg_trav *trav = seq->private;
	const struct xt_match *match;

	switch (trav->class) {
	case MTTG_TRAV_NFP_UNSPEC:
	case MTTG_TRAV_NFP_SPEC:
		if (trav->curr == trav->head)
			return 0;
		match = list_entry(trav->curr, struct xt_match, list);
		if (*match->name)
			seq_printf(seq, "%s\n", match->name);
	}
	return 0;
}
