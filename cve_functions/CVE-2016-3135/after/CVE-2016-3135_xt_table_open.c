static int xt_table_open(struct inode *inode, struct file *file)
{
	int ret;
	struct xt_names_priv *priv;

	ret = seq_open_net(inode, file, &xt_table_seq_ops,
			   sizeof(struct xt_names_priv));
	if (!ret) {
		priv = ((struct seq_file *)file->private_data)->private;
		priv->af = (unsigned long)PDE_DATA(inode);
	}
	return ret;
}
