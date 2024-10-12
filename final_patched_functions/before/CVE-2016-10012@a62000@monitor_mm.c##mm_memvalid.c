mm_memvalid(struct mm_master *mm, void *address, size_t size)
{
	void *end = (char *)address + size;

	if (address < mm->address)
		fatal("mm_memvalid: address too small: %p", address);
	if (end < address)
		fatal("mm_memvalid: end < address: %p < %p", end, address);
	if (end > MM_ADDRESS_END(mm))
		fatal("mm_memvalid: address too large: %p", address);
}
