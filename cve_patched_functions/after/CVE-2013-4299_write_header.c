static int write_header(struct pstore *ps)
{
	struct disk_header *dh;

	memset(ps->header_area, 0, ps->store->chunk_size << SECTOR_SHIFT);

	dh = ps->header_area;
	dh->magic = cpu_to_le32(SNAP_MAGIC);
	dh->valid = cpu_to_le32(ps->valid);
	dh->version = cpu_to_le32(ps->version);
	dh->chunk_size = cpu_to_le32(ps->store->chunk_size);

	return chunk_io(ps, ps->header_area, 0, WRITE, 1);
}
