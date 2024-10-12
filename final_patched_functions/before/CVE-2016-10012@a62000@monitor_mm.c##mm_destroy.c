mm_destroy(struct mm_master *mm)
{
	mm_freelist(mm->mmalloc, &mm->rb_free);
	mm_freelist(mm->mmalloc, &mm->rb_allocated);

	if (munmap(mm->address, mm->size) == -1)
		fatal("munmap(%p, %zu): %s", mm->address, mm->size,
		    strerror(errno));
	if (mm->mmalloc == NULL)
		free(mm);
	else
		mm_free(mm->mmalloc, mm);
}
