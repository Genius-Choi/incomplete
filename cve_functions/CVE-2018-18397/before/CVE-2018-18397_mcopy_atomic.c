ssize_t mcopy_atomic(struct mm_struct *dst_mm, unsigned long dst_start,
		     unsigned long src_start, unsigned long len,
		     bool *mmap_changing)
{
	return __mcopy_atomic(dst_mm, dst_start, src_start, len, false,
			      mmap_changing);
}
