xfs_file_llseek(
	struct file	*file,
	loff_t		offset,
	int		origin)
{
	switch (origin) {
	case SEEK_END:
	case SEEK_CUR:
	case SEEK_SET:
		return generic_file_llseek(file, offset, origin);
	case SEEK_DATA:
		return xfs_seek_data(file, offset);
	case SEEK_HOLE:
		return xfs_seek_hole(file, offset);
	default:
		return -EINVAL;
	}
}
