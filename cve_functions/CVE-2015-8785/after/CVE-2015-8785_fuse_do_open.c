int fuse_do_open(struct fuse_conn *fc, u64 nodeid, struct file *file,
		 bool isdir)
{
	struct fuse_file *ff;
	int opcode = isdir ? FUSE_OPENDIR : FUSE_OPEN;

	ff = fuse_file_alloc(fc);
	if (!ff)
		return -ENOMEM;

	ff->fh = 0;
	ff->open_flags = FOPEN_KEEP_CACHE; /* Default for no-open */
	if (!fc->no_open || isdir) {
		struct fuse_open_out outarg;
		int err;

		err = fuse_send_open(fc, nodeid, file, opcode, &outarg);
		if (!err) {
			ff->fh = outarg.fh;
			ff->open_flags = outarg.open_flags;

		} else if (err != -ENOSYS || isdir) {
			fuse_file_free(ff);
			return err;
		} else {
			fc->no_open = 1;
		}
	}

	if (isdir)
		ff->open_flags &= ~FOPEN_DIRECT_IO;

	ff->nodeid = nodeid;
	file->private_data = fuse_file_get(ff);

	return 0;
}
