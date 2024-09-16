static inline int should_follow_link(struct nameidata *nd, struct path *link,
				     int follow,
				     struct inode *inode, unsigned seq)
{
	if (likely(!d_is_symlink(link->dentry)))
		return 0;
	if (!follow)
		return 0;
	return pick_link(nd, link, inode, seq);
}
