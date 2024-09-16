static inline struct page *alloc_hugepage_vma(int defrag,
					      struct vm_area_struct *vma,
					      unsigned long haddr, int nd,
					      gfp_t extra_gfp)
{
	return alloc_pages_vma(alloc_hugepage_gfpmask(defrag, extra_gfp),
			       HPAGE_PMD_ORDER, vma, haddr, nd);
}
