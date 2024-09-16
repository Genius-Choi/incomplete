static inline int stack_guard_page(struct vm_area_struct *vma, unsigned long addr)
{
	return stack_guard_page_start(vma, addr) ||
	       stack_guard_page_end(vma, addr+PAGE_SIZE);
}
