static int vfat_find_form(struct inode *dir, unsigned char *name)
{
	struct fat_slot_info sinfo;
	int err = fat_scan(dir, name, &sinfo);
	if (err)
		return -ENOENT;
	brelse(sinfo.bh);
	return 0;
}
