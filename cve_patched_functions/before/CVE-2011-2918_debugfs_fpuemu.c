static int __init debugfs_fpuemu(void)
{
	struct dentry *d, *dir;

	if (!mips_debugfs_dir)
		return -ENODEV;
	dir = debugfs_create_dir("fpuemustats", mips_debugfs_dir);
	if (!dir)
		return -ENOMEM;

#define FPU_STAT_CREATE(M)						\
	do {								\
		d = debugfs_create_file(#M , S_IRUGO, dir,		\
			(void *)offsetof(struct mips_fpu_emulator_stats, M), \
			&fops_fpuemu_stat);				\
		if (!d)							\
			return -ENOMEM;					\
	} while (0)

	FPU_STAT_CREATE(emulated);
	FPU_STAT_CREATE(loads);
	FPU_STAT_CREATE(stores);
	FPU_STAT_CREATE(cp1ops);
	FPU_STAT_CREATE(cp1xops);
	FPU_STAT_CREATE(errors);

	return 0;
}
