static void madvise_free_page_range(struct mmu_gather *tlb,
			     struct vm_area_struct *vma,
			     unsigned long addr, unsigned long end)
{
	struct mm_walk free_walk = {
		.pmd_entry = madvise_free_pte_range,
		.mm = vma->vm_mm,
		.private = tlb,
	};

	tlb_start_vma(tlb, vma);
	walk_page_range(addr, end, &free_walk);
	tlb_end_vma(tlb, vma);
}
