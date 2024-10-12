mm_xmalloc(struct mm_master *mm, size_t size)
{
	void *address;

	address = mm_malloc(mm, size);
	if (address == NULL)
		fatal("%s: mm_malloc(%zu)", __func__, size);
	memset(address, 0, size);
	return (address);
}
