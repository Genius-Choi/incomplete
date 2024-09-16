void squashfs_closedir(struct dir *dir)
{
	free(dir->dirs);
	free(dir);
}
