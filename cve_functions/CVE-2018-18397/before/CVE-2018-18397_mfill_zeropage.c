ssize_t mfill_zeropage(struct mm_struct *dst_mm, unsigned long start,
		       unsigned long len, bool *mmap_changing)
{
	return __mcopy_atomic(dst_mm, start, 0, len, true, mmap_changing);
}
