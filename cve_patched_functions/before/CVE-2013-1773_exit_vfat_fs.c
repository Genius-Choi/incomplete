static void __exit exit_vfat_fs(void)
{
	unregister_filesystem(&vfat_fs_type);
}
