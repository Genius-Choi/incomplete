static struct disk_exception *get_exception(struct pstore *ps, uint32_t index)
{
	BUG_ON(index >= ps->exceptions_per_area);

	return ((struct disk_exception *) ps->area) + index;
}
