static struct bio *btrfs_dio_bio_alloc(struct block_device *bdev,
				       u64 first_sector, gfp_t gfp_flags)
{
	int nr_vecs = bio_get_nr_vecs(bdev);
	return btrfs_bio_alloc(bdev, first_sector, nr_vecs, gfp_flags);
}
