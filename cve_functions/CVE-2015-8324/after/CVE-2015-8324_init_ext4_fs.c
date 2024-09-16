static int __init init_ext4_fs(void)
{
	int err;

	err = init_ext4_system_zone();
	if (err)
		return err;
	ext4_kset = kset_create_and_add("ext4", NULL, fs_kobj);
	if (!ext4_kset)
		goto out4;
	ext4_proc_root = proc_mkdir("fs/ext4", NULL);
	err = init_ext4_mballoc();
	if (err)
		goto out3;

	err = init_ext4_xattr();
	if (err)
		goto out2;
	err = init_inodecache();
	if (err)
		goto out1;
	register_as_ext2();
	register_as_ext3();
	err = register_filesystem(&ext4_fs_type);
	if (err)
		goto out;
	return 0;
out:
	unregister_as_ext2();
	unregister_as_ext3();
	destroy_inodecache();
out1:
	exit_ext4_xattr();
out2:
	exit_ext4_mballoc();
out3:
	remove_proc_entry("fs/ext4", NULL);
	kset_unregister(ext4_kset);
out4:
	exit_ext4_system_zone();
	return err;
}
