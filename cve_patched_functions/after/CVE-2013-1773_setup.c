static void setup(struct super_block *sb)
{
	MSDOS_SB(sb)->dir_ops = &vfat_dir_inode_operations;
	if (MSDOS_SB(sb)->options.name_check != 's')
		sb->s_d_op = &vfat_ci_dentry_ops;
	else
		sb->s_d_op = &vfat_dentry_ops;
}
