void queue_dir(char *pathname, struct dir *dir)
{
	struct squashfs_file *file = malloc(sizeof(struct squashfs_file));
	if(file == NULL)
		EXIT_UNSQUASH("queue_dir: unable to malloc file\n");

	file->fd = -1;
	file->mode = dir->mode;
	file->gid = dir->guid;
	file->uid = dir->uid;
	file->time = dir->mtime;
	file->pathname = strdup(pathname);
	file->xattr = dir->xattr;
	queue_put(to_writer, file);
}
