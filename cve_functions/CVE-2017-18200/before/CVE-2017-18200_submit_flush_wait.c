static int submit_flush_wait(struct f2fs_sb_info *sbi)
{
	int ret = __submit_flush_wait(sbi, sbi->sb->s_bdev);
	int i;

	if (!sbi->s_ndevs || ret)
		return ret;

	for (i = 1; i < sbi->s_ndevs; i++) {
		ret = __submit_flush_wait(sbi, FDEV(i).bdev);
		if (ret)
			break;
	}
	return ret;
}
