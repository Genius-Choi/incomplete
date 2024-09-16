void mnt_set_mountpoint(struct mount *mnt, struct dentry *dentry,
			struct mount *child_mnt)
{
	mnt_add_count(mnt, 1);	/* essentially, that's mntget */
	child_mnt->mnt_mountpoint = dget(dentry);
	child_mnt->mnt_parent = mnt;
	spin_lock(&dentry->d_lock);
	dentry->d_flags |= DCACHE_MOUNTED;
	spin_unlock(&dentry->d_lock);
}
