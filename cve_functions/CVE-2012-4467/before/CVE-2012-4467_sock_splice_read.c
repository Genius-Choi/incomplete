static ssize_t sock_splice_read(struct file *file, loff_t *ppos,
				struct pipe_inode_info *pipe, size_t len,
				unsigned int flags)
{
	struct socket *sock = file->private_data;

	if (unlikely(!sock->ops->splice_read))
		return -EINVAL;

	sock_update_classid(sock->sk);

	return sock->ops->splice_read(sock, ppos, pipe, len, flags);
}
