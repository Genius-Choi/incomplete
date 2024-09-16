static void init_once(void *foo)
{
	struct hugetlbfs_inode_info *ei = (struct hugetlbfs_inode_info *)foo;

	inode_init_once(&ei->vfs_inode);
}
