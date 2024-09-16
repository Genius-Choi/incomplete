u8 kvm_get_guest_memory_type(struct kvm_vcpu *vcpu, gfn_t gfn)
{
	u8 mtrr;

	mtrr = get_mtrr_type(&vcpu->arch.mtrr_state, gfn << PAGE_SHIFT,
			     (gfn << PAGE_SHIFT) + PAGE_SIZE);
	if (mtrr == 0xfe || mtrr == 0xff)
		mtrr = MTRR_TYPE_WRBACK;
	return mtrr;
}
