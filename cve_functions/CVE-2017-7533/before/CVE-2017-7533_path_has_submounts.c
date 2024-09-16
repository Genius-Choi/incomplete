int path_has_submounts(const struct path *parent)
{
	struct check_mount data = { .mnt = parent->mnt, .mounted = 0 };

	read_seqlock_excl(&mount_lock);
	d_walk(parent->dentry, &data, path_check_mount, NULL);
	read_sequnlock_excl(&mount_lock);

	return data.mounted;
}
