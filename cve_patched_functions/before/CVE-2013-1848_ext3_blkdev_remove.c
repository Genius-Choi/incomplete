static int ext3_blkdev_remove(struct ext3_sb_info *sbi)
{
	struct block_device *bdev;
	int ret = -ENODEV;

	bdev = sbi->journal_bdev;
	if (bdev) {
		ret = ext3_blkdev_put(bdev);
		sbi->journal_bdev = NULL;
	}
	return ret;
}
