static void *xt_table_seq_next(struct seq_file *seq, void *v, loff_t *pos)
{
	struct xt_names_priv *priv = seq->private;
	struct net *net = seq_file_net(seq);
	u_int8_t af = priv->af;

	return seq_list_next(v, &net->xt.tables[af], pos);
}
