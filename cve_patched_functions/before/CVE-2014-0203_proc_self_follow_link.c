static void *proc_self_follow_link(struct dentry *dentry, struct nameidata *nd)
{
	struct pid_namespace *ns = dentry->d_sb->s_fs_info;
	pid_t tgid = task_tgid_nr_ns(current, ns);
	char tmp[PROC_NUMBUF];
	if (!tgid)
		return ERR_PTR(-ENOENT);
	sprintf(tmp, "%d", task_tgid_nr_ns(current, ns));
	return ERR_PTR(vfs_follow_link(nd,tmp));
}
