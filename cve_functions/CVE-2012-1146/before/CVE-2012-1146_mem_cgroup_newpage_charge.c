int mem_cgroup_newpage_charge(struct page *page,
			      struct mm_struct *mm, gfp_t gfp_mask)
{
	if (mem_cgroup_disabled())
		return 0;
	VM_BUG_ON(page_mapped(page));
	VM_BUG_ON(page->mapping && !PageAnon(page));
	VM_BUG_ON(!mm);
	return mem_cgroup_charge_common(page, mm, gfp_mask,
					MEM_CGROUP_CHARGE_TYPE_MAPPED);
}
