static sector_t flakey_map_sector(struct dm_target *ti, sector_t bi_sector)
{
	struct flakey_c *fc = ti->private;

	return fc->start + dm_target_offset(ti, bi_sector);
}
