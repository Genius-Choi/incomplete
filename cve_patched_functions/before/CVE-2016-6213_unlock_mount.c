static void unlock_mount(struct mountpoint *where)
{
	struct dentry *dentry = where->m_dentry;
	put_mountpoint(where);
	namespace_unlock();
	inode_unlock(dentry->d_inode);
}
