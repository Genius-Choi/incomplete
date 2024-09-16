int zap_huge_pmd(struct mmu_gather *tlb, struct vm_area_struct *vma,
		 pmd_t *pmd)
{
	int ret = 0;

	spin_lock(&tlb->mm->page_table_lock);
	if (likely(pmd_trans_huge(*pmd))) {
		if (unlikely(pmd_trans_splitting(*pmd))) {
			spin_unlock(&tlb->mm->page_table_lock);
			wait_split_huge_page(vma->anon_vma,
					     pmd);
		} else {
			struct page *page;
			pgtable_t pgtable;
			pgtable = get_pmd_huge_pte(tlb->mm);
			page = pmd_page(*pmd);
			pmd_clear(pmd);
			page_remove_rmap(page);
			VM_BUG_ON(page_mapcount(page) < 0);
			add_mm_counter(tlb->mm, MM_ANONPAGES, -HPAGE_PMD_NR);
			VM_BUG_ON(!PageHead(page));
			spin_unlock(&tlb->mm->page_table_lock);
			tlb_remove_page(tlb, page);
			pte_free(tlb->mm, pgtable);
			ret = 1;
		}
	} else
		spin_unlock(&tlb->mm->page_table_lock);

	return ret;
}
