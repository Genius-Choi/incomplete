void queue_file(char *pathname, int file_fd, struct inode *inode)
{
	struct squashfs_file *file = malloc(sizeof(struct squashfs_file));
	if(file == NULL)
		EXIT_UNSQUASH("queue_file: unable to malloc file\n");

	file->fd = file_fd;
	file->file_size = inode->data;
	file->mode = inode->mode;
	file->gid = inode->gid;
	file->uid = inode->uid;
	file->time = inode->time;
	file->pathname = strdup(pathname);
	file->blocks = inode->blocks + (inode->frag_bytes > 0);
	file->sparse = inode->sparse;
	file->xattr = inode->xattr;
	queue_put(to_writer, file);
}
