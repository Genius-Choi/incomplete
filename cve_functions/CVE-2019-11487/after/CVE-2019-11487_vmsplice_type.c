static int vmsplice_type(struct fd f, int *type)
{
	if (!f.file)
		return -EBADF;
	if (f.file->f_mode & FMODE_WRITE) {
		*type = WRITE;
	} else if (f.file->f_mode & FMODE_READ) {
		*type = READ;
	} else {
		fdput(f);
		return -EBADF;
	}
	return 0;
}
