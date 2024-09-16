static struct page *khugepaged_alloc_hugepage(void)
{
	struct page *hpage;

	do {
		hpage = alloc_hugepage(khugepaged_defrag());
		if (!hpage) {
			count_vm_event(THP_COLLAPSE_ALLOC_FAILED);
			khugepaged_alloc_sleep();
		} else
			count_vm_event(THP_COLLAPSE_ALLOC);
	} while (unlikely(!hpage) &&
		 likely(khugepaged_enabled()));
	return hpage;
}
