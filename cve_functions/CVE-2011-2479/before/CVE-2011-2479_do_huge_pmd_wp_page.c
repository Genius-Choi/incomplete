int do_huge_pmd_wp_page(struct mm_struct *mm, struct vm_area_struct *vma,
			unsigned long address, pmd_t *pmd, pmd_t orig_pmd)
{
	int ret = 0;
	struct page *page, *new_page;
	unsigned long haddr;

	VM_BUG_ON(!vma->anon_vma);
	spin_lock(&mm->page_table_lock);
	if (unlikely(!pmd_same(*pmd, orig_pmd)))
		goto out_unlock;

	page = pmd_page(orig_pmd);
	VM_BUG_ON(!PageCompound(page) || !PageHead(page));
	haddr = address & HPAGE_PMD_MASK;
	if (page_mapcount(page) == 1) {
		pmd_t entry;
		entry = pmd_mkyoung(orig_pmd);
		entry = maybe_pmd_mkwrite(pmd_mkdirty(entry), vma);
		if (pmdp_set_access_flags(vma, haddr, pmd, entry,  1))
			update_mmu_cache(vma, address, entry);
		ret |= VM_FAULT_WRITE;
		goto out_unlock;
	}
	get_page(page);
	spin_unlock(&mm->page_table_lock);

	if (transparent_hugepage_enabled(vma) &&
	    !transparent_hugepage_debug_cow())
		new_page = alloc_hugepage_vma(transparent_hugepage_defrag(vma),
					      vma, haddr, numa_node_id(), 0);
	else
		new_page = NULL;

	if (unlikely(!new_page)) {
		count_vm_event(THP_FAULT_FALLBACK);
		ret = do_huge_pmd_wp_page_fallback(mm, vma, address,
						   pmd, orig_pmd, page, haddr);
		put_page(page);
		goto out;
	}
	count_vm_event(THP_FAULT_ALLOC);

	if (unlikely(mem_cgroup_newpage_charge(new_page, mm, GFP_KERNEL))) {
		put_page(new_page);
		put_page(page);
		ret |= VM_FAULT_OOM;
		goto out;
	}

	copy_user_huge_page(new_page, page, haddr, vma, HPAGE_PMD_NR);
	__SetPageUptodate(new_page);

	spin_lock(&mm->page_table_lock);
	put_page(page);
	if (unlikely(!pmd_same(*pmd, orig_pmd))) {
		mem_cgroup_uncharge_page(new_page);
		put_page(new_page);
	} else {
		pmd_t entry;
		VM_BUG_ON(!PageHead(page));
		entry = mk_pmd(new_page, vma->vm_page_prot);
		entry = maybe_pmd_mkwrite(pmd_mkdirty(entry), vma);
		entry = pmd_mkhuge(entry);
		pmdp_clear_flush_notify(vma, haddr, pmd);
		page_add_new_anon_rmap(new_page, vma, haddr);
		set_pmd_at(mm, haddr, pmd, entry);
		update_mmu_cache(vma, address, entry);
		page_remove_rmap(page);
		put_page(page);
		ret |= VM_FAULT_WRITE;
	}
out_unlock:
	spin_unlock(&mm->page_table_lock);
out:
	return ret;
}
