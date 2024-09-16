static int alloc_identity_pagetable(struct kvm *kvm)
{
	/* Called with kvm->slots_lock held. */

	int r = 0;

	BUG_ON(kvm->arch.ept_identity_pagetable_done);

	r = __x86_set_memory_region(kvm, IDENTITY_PAGETABLE_PRIVATE_MEMSLOT,
				    kvm->arch.ept_identity_map_addr, PAGE_SIZE);

	return r;
}
