static struct dentry *bpf_mount(struct file_system_type *type, int flags,
				const char *dev_name, void *data)
{
	return mount_ns(type, flags, current->nsproxy->mnt_ns, bpf_fill_super);
}
