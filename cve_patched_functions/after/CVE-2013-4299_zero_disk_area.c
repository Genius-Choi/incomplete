static int zero_disk_area(struct pstore *ps, chunk_t area)
{
	return chunk_io(ps, ps->zero_area, area_location(ps, area), WRITE, 0);
}
