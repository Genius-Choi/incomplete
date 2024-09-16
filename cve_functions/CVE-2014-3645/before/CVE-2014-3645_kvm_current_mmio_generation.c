static unsigned int kvm_current_mmio_generation(struct kvm *kvm)
{
	/*
	 * Init kvm generation close to MMIO_MAX_GEN to easily test the
	 * code of handling generation number wrap-around.
	 */
	return (kvm_memslots(kvm)->generation +
		      MMIO_MAX_GEN - 150) & MMIO_GEN_MASK;
}
