static int bpf_mkobj(struct inode *dir, struct dentry *dentry, umode_t mode,
		     dev_t devt)
{
	enum bpf_type type = MINOR(devt);

	if (MAJOR(devt) != UNNAMED_MAJOR || !S_ISREG(mode) ||
	    dentry->d_fsdata == NULL)
		return -EPERM;

	switch (type) {
	case BPF_TYPE_PROG:
		return bpf_mkobj_ops(dir, dentry, mode, &bpf_prog_iops);
	case BPF_TYPE_MAP:
		return bpf_mkobj_ops(dir, dentry, mode, &bpf_map_iops);
	default:
		return -EPERM;
	}
}
