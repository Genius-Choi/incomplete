void kvm_after_handle_nmi(struct kvm_vcpu *vcpu)
{
	percpu_write(current_vcpu, NULL);
}
