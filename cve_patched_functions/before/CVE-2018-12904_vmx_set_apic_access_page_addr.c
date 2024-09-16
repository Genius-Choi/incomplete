static void vmx_set_apic_access_page_addr(struct kvm_vcpu *vcpu, hpa_t hpa)
{
	if (!is_guest_mode(vcpu)) {
		vmcs_write64(APIC_ACCESS_ADDR, hpa);
		vmx_flush_tlb(vcpu, true);
	}
}
