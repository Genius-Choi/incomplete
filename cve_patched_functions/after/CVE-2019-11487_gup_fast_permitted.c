bool gup_fast_permitted(unsigned long start, int nr_pages)
{
	unsigned long len, end;

	len = (unsigned long) nr_pages << PAGE_SHIFT;
	end = start + len;
	return end >= start;
}
