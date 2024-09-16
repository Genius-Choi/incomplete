u64 kvm_read_l1_tsc(struct kvm_vcpu *vcpu, u64 host_tsc)
{
	return kvm_x86_ops->read_l1_tsc(vcpu, kvm_scale_tsc(vcpu, host_tsc));
}
