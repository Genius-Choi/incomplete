memcheck_ptr_cmp(MEMCHECK *m1, MEMCHECK *m2)
{
	return m1->ptr - m2->ptr;
}
