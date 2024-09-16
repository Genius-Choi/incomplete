static int vfat_fill_super(struct super_block *sb, void *data, int silent)
{
	return fat_fill_super(sb, data, silent, 1, setup);
}
