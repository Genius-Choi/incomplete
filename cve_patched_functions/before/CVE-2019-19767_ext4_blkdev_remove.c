static void ext4_blkdev_remove(struct ext4_sb_info *sbi)
{
	struct block_device *bdev;
	bdev = sbi->journal_bdev;
	if (bdev) {
		ext4_blkdev_put(bdev);
		sbi->journal_bdev = NULL;
	}
}
