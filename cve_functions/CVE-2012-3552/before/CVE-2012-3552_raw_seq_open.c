int raw_seq_open(struct inode *ino, struct file *file,
		 struct raw_hashinfo *h, const struct seq_operations *ops)
{
	int err;
	struct raw_iter_state *i;

	err = seq_open_net(ino, file, ops, sizeof(struct raw_iter_state));
	if (err < 0)
		return err;

	i = raw_seq_private((struct seq_file *)file->private_data);
	i->h = h;
	return 0;
}
