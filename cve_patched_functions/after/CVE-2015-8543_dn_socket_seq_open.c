static int dn_socket_seq_open(struct inode *inode, struct file *file)
{
	return seq_open_private(file, &dn_socket_seq_ops,
			sizeof(struct dn_iter_state));
}
