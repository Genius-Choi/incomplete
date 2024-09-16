static void vmx_set_cr3(struct kvm_vcpu *vcpu, unsigned long cr3)
{
	unsigned long guest_cr3;
	u64 eptp;

	guest_cr3 = cr3;
	if (enable_ept) {
		eptp = construct_eptp(vcpu, cr3);
		vmcs_write64(EPT_POINTER, eptp);
		if (enable_unrestricted_guest || is_paging(vcpu) ||
		    is_guest_mode(vcpu))
			guest_cr3 = kvm_read_cr3(vcpu);
		else
			guest_cr3 = to_kvm_vmx(vcpu->kvm)->ept_identity_map_addr;
		ept_load_pdptrs(vcpu);
	}

	vmx_flush_tlb(vcpu, true);
	vmcs_writel(GUEST_CR3, guest_cr3);
}
