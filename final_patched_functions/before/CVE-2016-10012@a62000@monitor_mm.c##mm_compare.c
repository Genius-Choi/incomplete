mm_compare(struct mm_share *a, struct mm_share *b)
{
	ptrdiff_t diff = (char *)a->address - (char *)b->address;

	if (diff == 0)
		return (0);
	else if (diff < 0)
		return (-1);
	else
		return (1);
}
