static void zero_memory_area(struct pstore *ps)
{
	memset(ps->area, 0, ps->store->chunk_size << SECTOR_SHIFT);
}
