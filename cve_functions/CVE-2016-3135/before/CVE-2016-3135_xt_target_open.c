static int xt_target_open(struct inode *inode, struct file *file)
{
	struct nf_mttg_trav *trav;
	trav = __seq_open_private(file, &xt_target_seq_ops, sizeof(*trav));
	if (!trav)
		return -ENOMEM;

	trav->nfproto = (unsigned long)PDE_DATA(inode);
	return 0;
}
