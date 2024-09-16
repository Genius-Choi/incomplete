static inline bool PageHugeTemporary(struct page *page)
{
	if (!PageHuge(page))
		return false;

	return (unsigned long)page[2].mapping == -1U;
}
