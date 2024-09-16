static void *xt_table_seq_start(struct seq_file *seq, loff_t *pos)
{
	struct xt_names_priv *priv = seq->private;
	struct net *net = seq_file_net(seq);
	u_int8_t af = priv->af;

	mutex_lock(&xt[af].mutex);
	return seq_list_start(&net->xt.tables[af], *pos);
}
