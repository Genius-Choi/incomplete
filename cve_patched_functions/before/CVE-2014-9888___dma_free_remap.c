static void __dma_free_remap(void *cpu_addr, size_t size)
{
	unsigned int flags = VM_ARM_DMA_CONSISTENT | VM_USERMAP;
	struct vm_struct *area = find_vm_area(cpu_addr);
	if (!area || (area->flags & flags) != flags) {
		WARN(1, "trying to free invalid coherent area: %p\n", cpu_addr);
		return;
	}
	unmap_kernel_range((unsigned long)cpu_addr, size);
	vunmap(cpu_addr);
}
