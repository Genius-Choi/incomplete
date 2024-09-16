static int xt_target_seq_show(struct seq_file *seq, void *v)
{
	const struct nf_mttg_trav *trav = seq->private;
	const struct xt_target *target;

	switch (trav->class) {
	case MTTG_TRAV_NFP_UNSPEC:
	case MTTG_TRAV_NFP_SPEC:
		if (trav->curr == trav->head)
			return 0;
		target = list_entry(trav->curr, struct xt_target, list);
		if (*target->name)
			seq_printf(seq, "%s\n", target->name);
	}
	return 0;
}
