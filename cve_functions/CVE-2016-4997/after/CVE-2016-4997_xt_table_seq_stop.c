static void xt_table_seq_stop(struct seq_file *seq, void *v)
{
	struct xt_names_priv *priv = seq->private;
	u_int8_t af = priv->af;

	mutex_unlock(&xt[af].mutex);
}
