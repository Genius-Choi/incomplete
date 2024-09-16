static u32 calc_checksum(struct page *page)
{
	u32 checksum;
	void *addr = kmap_atomic(page, KM_USER0);
	checksum = jhash2(addr, PAGE_SIZE / 4, 17);
	kunmap_atomic(addr, KM_USER0);
	return checksum;
}
