static inline void SetPageHugeTemporary(struct page *page)
{
	page[2].mapping = (void *)-1U;
}
