static int kvm_vcpu_ioctl_smi(struct kvm_vcpu *vcpu)
{
	kvm_make_request(KVM_REQ_SMI, vcpu);

	return 0;
}
