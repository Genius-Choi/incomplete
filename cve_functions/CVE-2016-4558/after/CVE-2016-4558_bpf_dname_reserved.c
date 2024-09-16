static bool bpf_dname_reserved(const struct dentry *dentry)
{
	return strchr(dentry->d_name.name, '.');
}
