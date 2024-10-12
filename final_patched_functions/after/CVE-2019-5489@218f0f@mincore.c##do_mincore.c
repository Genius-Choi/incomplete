static long do_mincore(unsigned long addr, unsigned long pages, unsigned char *vec)
{
	struct vm_area_struct *vma;
	unsigned long end;
	int err;
	struct mm_walk mincore_walk = {
		.pmd_entry = mincore_pte_range,
		.pte_hole = mincore_unmapped_range,
		.hugetlb_entry = mincore_hugetlb,
		.private = vec,
	};

	vma = find_vma(current->mm, addr);
	if (!vma || addr < vma->vm_start)
		return -ENOMEM;
	mincore_walk.mm = vma->vm_mm;
	end = min(vma->vm_end, addr + (pages << PAGE_SHIFT));
	err = walk_page_range(addr, end, &mincore_walk);
	if (err < 0)
		return err;
	return (end - addr) >> PAGE_SHIFT;
}
