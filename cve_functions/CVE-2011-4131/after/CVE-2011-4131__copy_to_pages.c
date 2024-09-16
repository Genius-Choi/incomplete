_copy_to_pages(struct page **pages, size_t pgbase, const char *p, size_t len)
{
	struct page **pgto;
	char *vto;
	size_t copy;

	pgto = pages + (pgbase >> PAGE_CACHE_SHIFT);
	pgbase &= ~PAGE_CACHE_MASK;

	for (;;) {
		copy = PAGE_CACHE_SIZE - pgbase;
		if (copy > len)
			copy = len;

		vto = kmap_atomic(*pgto, KM_USER0);
		memcpy(vto + pgbase, p, copy);
		kunmap_atomic(vto, KM_USER0);

		len -= copy;
		if (len == 0)
			break;

		pgbase += copy;
		if (pgbase == PAGE_CACHE_SIZE) {
			flush_dcache_page(*pgto);
			pgbase = 0;
			pgto++;
		}
		p += copy;
	}
	flush_dcache_page(*pgto);
}
