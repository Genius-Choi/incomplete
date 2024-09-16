static int nfsd_buffered_filldir(struct dir_context *ctx, const char *name,
				 int namlen, loff_t offset, u64 ino,
				 unsigned int d_type)
{
	struct readdir_data *buf =
		container_of(ctx, struct readdir_data, ctx);
	struct buffered_dirent *de = (void *)(buf->dirent + buf->used);
	unsigned int reclen;

	reclen = ALIGN(sizeof(struct buffered_dirent) + namlen, sizeof(u64));
	if (buf->used + reclen > PAGE_SIZE) {
		buf->full = 1;
		return -EINVAL;
	}

	de->namlen = namlen;
	de->offset = offset;
	de->ino = ino;
	de->d_type = d_type;
	memcpy(de->name, name, namlen);
	buf->used += reclen;

	return 0;
}
