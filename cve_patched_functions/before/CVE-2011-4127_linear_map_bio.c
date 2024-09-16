static void linear_map_bio(struct dm_target *ti, struct bio *bio)
{
	struct linear_c *lc = ti->private;

	bio->bi_bdev = lc->dev->bdev;
	if (bio_sectors(bio))
		bio->bi_sector = linear_map_sector(ti, bio->bi_sector);
}
