static int vmx_set_tss_addr(struct kvm *kvm, unsigned int addr)
{
	int ret;

	if (enable_unrestricted_guest)
		return 0;

	ret = x86_set_memory_region(kvm, TSS_PRIVATE_MEMSLOT, addr,
				    PAGE_SIZE * 3);
	if (ret)
		return ret;
	to_kvm_vmx(kvm)->tss_addr = addr;
	return init_rmode_tss(kvm);
}
