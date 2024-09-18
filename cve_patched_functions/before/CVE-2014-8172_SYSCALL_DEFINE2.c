SYSCALL_DEFINE2(fchmod, unsigned int, fd, umode_t, mode)
{
	struct fd f = fdget(fd);
	int err = -EBADF;

	if (f.file) {
		audit_inode(NULL, f.file->f_path.dentry, 0);
		err = chmod_common(&f.file->f_path, mode);
		fdput(f);
	}
	return err;
}
