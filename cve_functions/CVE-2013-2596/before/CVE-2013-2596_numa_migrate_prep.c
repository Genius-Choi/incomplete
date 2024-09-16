int numa_migrate_prep(struct page *page, struct vm_area_struct *vma,
				unsigned long addr, int current_nid)
{
	get_page(page);

	count_vm_numa_event(NUMA_HINT_FAULTS);
	if (current_nid == numa_node_id())
		count_vm_numa_event(NUMA_HINT_FAULTS_LOCAL);

	return mpol_misplaced(page, vma, addr);
}
