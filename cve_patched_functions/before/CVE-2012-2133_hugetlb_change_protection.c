void hugetlb_change_protection(struct vm_area_struct *vma,
		unsigned long address, unsigned long end, pgprot_t newprot)
{
	struct mm_struct *mm = vma->vm_mm;
	unsigned long start = address;
	pte_t *ptep;
	pte_t pte;
	struct hstate *h = hstate_vma(vma);

	BUG_ON(address >= end);
	flush_cache_range(vma, address, end);

	mutex_lock(&vma->vm_file->f_mapping->i_mmap_mutex);
	spin_lock(&mm->page_table_lock);
	for (; address < end; address += huge_page_size(h)) {
		ptep = huge_pte_offset(mm, address);
		if (!ptep)
			continue;
		if (huge_pmd_unshare(mm, &address, ptep))
			continue;
		if (!huge_pte_none(huge_ptep_get(ptep))) {
			pte = huge_ptep_get_and_clear(mm, address, ptep);
			pte = pte_mkhuge(pte_modify(pte, newprot));
			set_huge_pte_at(mm, address, ptep, pte);
		}
	}
	spin_unlock(&mm->page_table_lock);
	mutex_unlock(&vma->vm_file->f_mapping->i_mmap_mutex);

	flush_tlb_range(vma, start, end);
}
