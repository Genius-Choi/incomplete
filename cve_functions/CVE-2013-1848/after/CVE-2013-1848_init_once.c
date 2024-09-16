static void init_once(void *foo)
{
	struct ext3_inode_info *ei = (struct ext3_inode_info *) foo;

	INIT_LIST_HEAD(&ei->i_orphan);
#ifdef CONFIG_EXT3_FS_XATTR
	init_rwsem(&ei->xattr_sem);
#endif
	mutex_init(&ei->truncate_mutex);
	inode_init_once(&ei->vfs_inode);
}
