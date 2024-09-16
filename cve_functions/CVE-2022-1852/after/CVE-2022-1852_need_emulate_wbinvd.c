static bool need_emulate_wbinvd(struct kvm_vcpu *vcpu)
{
	return kvm_arch_has_noncoherent_dma(vcpu->kvm);
}
