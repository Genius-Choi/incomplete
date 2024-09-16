static int __init init_vfat_fs(void)
{
	return register_filesystem(&vfat_fs_type);
}
