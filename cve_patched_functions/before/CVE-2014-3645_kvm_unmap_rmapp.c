static int kvm_unmap_rmapp(struct kvm *kvm, unsigned long *rmapp,
			   struct kvm_memory_slot *slot, unsigned long data)
{
	u64 *sptep;
	struct rmap_iterator iter;
	int need_tlb_flush = 0;

	while ((sptep = rmap_get_first(*rmapp, &iter))) {
		BUG_ON(!(*sptep & PT_PRESENT_MASK));
		rmap_printk("kvm_rmap_unmap_hva: spte %p %llx\n", sptep, *sptep);

		drop_spte(kvm, sptep);
		need_tlb_flush = 1;
	}

	return need_tlb_flush;
}
