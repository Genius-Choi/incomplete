static void __exit exit_hugetlbfs_fs(void)
{
	kmem_cache_destroy(hugetlbfs_inode_cachep);
	kern_unmount(hugetlbfs_vfsmount);
	unregister_filesystem(&hugetlbfs_fs_type);
	bdi_destroy(&hugetlbfs_backing_dev_info);
}
