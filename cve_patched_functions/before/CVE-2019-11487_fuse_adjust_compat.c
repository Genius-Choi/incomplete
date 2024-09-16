static void fuse_adjust_compat(struct fuse_conn *fc, struct fuse_args *args)
{
	if (fc->minor < 4 && args->in.h.opcode == FUSE_STATFS)
		args->out.args[0].size = FUSE_COMPAT_STATFS_SIZE;

	if (fc->minor < 9) {
		switch (args->in.h.opcode) {
		case FUSE_LOOKUP:
		case FUSE_CREATE:
		case FUSE_MKNOD:
		case FUSE_MKDIR:
		case FUSE_SYMLINK:
		case FUSE_LINK:
			args->out.args[0].size = FUSE_COMPAT_ENTRY_OUT_SIZE;
			break;
		case FUSE_GETATTR:
		case FUSE_SETATTR:
			args->out.args[0].size = FUSE_COMPAT_ATTR_OUT_SIZE;
			break;
		}
	}
	if (fc->minor < 12) {
		switch (args->in.h.opcode) {
		case FUSE_CREATE:
			args->in.args[0].size = sizeof(struct fuse_open_in);
			break;
		case FUSE_MKNOD:
			args->in.args[0].size = FUSE_COMPAT_MKNOD_IN_SIZE;
			break;
		}
	}
}
