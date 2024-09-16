void local_flush_tlb_page(struct vm_area_struct *vma, unsigned long page)
{
	unsigned long flags;

	if (vma->vm_mm) {
		page &= PAGE_MASK;
		local_irq_save(flags);
		local_flush_tlb_one(get_asid(), page);
		local_irq_restore(flags);
	}
}
