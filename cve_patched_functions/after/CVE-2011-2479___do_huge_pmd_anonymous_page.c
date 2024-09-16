static int __do_huge_pmd_anonymous_page(struct mm_struct *mm,
					struct vm_area_struct *vma,
					unsigned long haddr, pmd_t *pmd,
					struct page *page)
{
	int ret = 0;
	pgtable_t pgtable;

	VM_BUG_ON(!PageCompound(page));
	pgtable = pte_alloc_one(mm, haddr);
	if (unlikely(!pgtable)) {
		mem_cgroup_uncharge_page(page);
		put_page(page);
		return VM_FAULT_OOM;
	}

	clear_huge_page(page, haddr, HPAGE_PMD_NR);
	__SetPageUptodate(page);

	spin_lock(&mm->page_table_lock);
	if (unlikely(!pmd_none(*pmd))) {
		spin_unlock(&mm->page_table_lock);
		mem_cgroup_uncharge_page(page);
		put_page(page);
		pte_free(mm, pgtable);
	} else {
		pmd_t entry;
		entry = mk_pmd(page, vma->vm_page_prot);
		entry = maybe_pmd_mkwrite(pmd_mkdirty(entry), vma);
		entry = pmd_mkhuge(entry);
		/*
		 * The spinlocking to take the lru_lock inside
		 * page_add_new_anon_rmap() acts as a full memory
		 * barrier to be sure clear_huge_page writes become
		 * visible after the set_pmd_at() write.
		 */
		page_add_new_anon_rmap(page, vma, haddr);
		set_pmd_at(mm, haddr, pmd, entry);
		prepare_pmd_huge_pte(pgtable, mm);
		add_mm_counter(mm, MM_ANONPAGES, HPAGE_PMD_NR);
		spin_unlock(&mm->page_table_lock);
	}

	return ret;
}
