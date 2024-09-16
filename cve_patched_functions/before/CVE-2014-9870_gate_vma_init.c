static int __init gate_vma_init(void)
{
	gate_vma.vm_page_prot = PAGE_READONLY_EXEC;
	return 0;
}
