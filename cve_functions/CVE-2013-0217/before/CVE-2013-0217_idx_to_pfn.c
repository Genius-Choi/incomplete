static inline unsigned long idx_to_pfn(struct xen_netbk *netbk,
				       u16 idx)
{
	return page_to_pfn(netbk->mmap_pages[idx]);
}
