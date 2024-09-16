static int get_fs_path(struct task_struct *task, struct path *path, bool root)
{
	struct fs_struct *fs;
	int result = -ENOENT;

	task_lock(task);
	fs = task->fs;
	if (fs) {
		read_lock(&fs->lock);
		*path = root ? fs->root : fs->pwd;
		path_get(path);
		read_unlock(&fs->lock);
		result = 0;
	}
	task_unlock(task);
	return result;
}
