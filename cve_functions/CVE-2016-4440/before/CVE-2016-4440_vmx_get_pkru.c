static u32 vmx_get_pkru(struct kvm_vcpu *vcpu)
{
	return to_vmx(vcpu)->guest_pkru;
}
