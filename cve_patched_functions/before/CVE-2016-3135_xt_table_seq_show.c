static int xt_table_seq_show(struct seq_file *seq, void *v)
{
	struct xt_table *table = list_entry(v, struct xt_table, list);

	if (*table->name)
		seq_printf(seq, "%s\n", table->name);
	return 0;
}
