static void __exit exit_ext4_fs(void)
{
	unregister_as_ext2();
	unregister_as_ext3();
	unregister_filesystem(&ext4_fs_type);
	destroy_inodecache();
	exit_ext4_xattr();
	exit_ext4_mballoc();
	remove_proc_entry("fs/ext4", NULL);
	kset_unregister(ext4_kset);
	exit_ext4_system_zone();
}
