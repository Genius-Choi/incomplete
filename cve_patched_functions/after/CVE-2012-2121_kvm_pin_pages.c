static pfn_t kvm_pin_pages(struct kvm *kvm, struct kvm_memory_slot *slot,
			   gfn_t gfn, unsigned long size)
{
	gfn_t end_gfn;
	pfn_t pfn;

	pfn     = gfn_to_pfn_memslot(kvm, slot, gfn);
	end_gfn = gfn + (size >> PAGE_SHIFT);
	gfn    += 1;

	if (is_error_pfn(pfn))
		return pfn;

	while (gfn < end_gfn)
		gfn_to_pfn_memslot(kvm, slot, gfn++);

	return pfn;
}
