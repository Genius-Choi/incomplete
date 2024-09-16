static inline void ClearPageHugeTemporary(struct page *page)
{
	page[2].mapping = NULL;
}
