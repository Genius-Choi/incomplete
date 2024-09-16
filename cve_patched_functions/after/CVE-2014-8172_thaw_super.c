int thaw_super(struct super_block *sb)
{
	int error;

	down_write(&sb->s_umount);
	if (sb->s_writers.frozen == SB_UNFROZEN) {
		up_write(&sb->s_umount);
		return -EINVAL;
	}

	if (sb->s_flags & MS_RDONLY)
		goto out;

	if (sb->s_op->unfreeze_fs) {
		error = sb->s_op->unfreeze_fs(sb);
		if (error) {
			printk(KERN_ERR
				"VFS:Filesystem thaw failed\n");
			up_write(&sb->s_umount);
			return error;
		}
	}

out:
	sb->s_writers.frozen = SB_UNFROZEN;
	smp_wmb();
	wake_up(&sb->s_writers.wait_unfrozen);
	deactivate_locked_super(sb);

	return 0;
}
