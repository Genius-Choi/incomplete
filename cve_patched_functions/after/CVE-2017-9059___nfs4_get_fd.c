__nfs4_get_fd(struct nfs4_file *f, int oflag)
{
	if (f->fi_fds[oflag])
		return get_file(f->fi_fds[oflag]);
	return NULL;
}
