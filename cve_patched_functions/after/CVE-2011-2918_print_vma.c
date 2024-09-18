static inline void print_vma(struct vm_area_struct *vma)
{
	printk("vma start 0x%08lx\n", vma->vm_start);
	printk("vma end   0x%08lx\n", vma->vm_end);

	print_prots(vma->vm_page_prot);
	printk("vm_flags 0x%08lx\n", vma->vm_flags);
}
