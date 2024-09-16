int change_huge_pmd(struct vm_area_struct *vma, pmd_t *pmd,
		unsigned long addr, pgprot_t newprot)
{
	struct mm_struct *mm = vma->vm_mm;
	int ret = 0;

	spin_lock(&mm->page_table_lock);
	if (likely(pmd_trans_huge(*pmd))) {
		if (unlikely(pmd_trans_splitting(*pmd))) {
			spin_unlock(&mm->page_table_lock);
			wait_split_huge_page(vma->anon_vma, pmd);
		} else {
			pmd_t entry;

			entry = pmdp_get_and_clear(mm, addr, pmd);
			entry = pmd_modify(entry, newprot);
			set_pmd_at(mm, addr, pmd, entry);
			spin_unlock(&vma->vm_mm->page_table_lock);
			flush_tlb_range(vma, addr, addr + HPAGE_PMD_SIZE);
			ret = 1;
		}
	} else
		spin_unlock(&vma->vm_mm->page_table_lock);

	return ret;
}
