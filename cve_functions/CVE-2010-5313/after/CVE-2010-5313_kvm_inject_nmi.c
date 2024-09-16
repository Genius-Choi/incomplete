void kvm_inject_nmi(struct kvm_vcpu *vcpu)
{
	kvm_make_request(KVM_REQ_EVENT, vcpu);
	vcpu->arch.nmi_pending = 1;
}
