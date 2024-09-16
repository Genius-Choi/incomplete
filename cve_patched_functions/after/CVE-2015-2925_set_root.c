static void set_root(struct nameidata *nd)
{
	get_fs_root(current->fs, &nd->root);
}
