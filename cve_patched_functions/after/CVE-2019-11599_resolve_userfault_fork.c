static int resolve_userfault_fork(struct userfaultfd_ctx *ctx,
				  struct userfaultfd_ctx *new,
				  struct uffd_msg *msg)
{
	int fd;

	fd = anon_inode_getfd("[userfaultfd]", &userfaultfd_fops, new,
			      O_RDWR | (new->flags & UFFD_SHARED_FCNTL_FLAGS));
	if (fd < 0)
		return fd;

	msg->arg.reserved.reserved1 = 0;
	msg->arg.fork.ufd = fd;
	return 0;
}
