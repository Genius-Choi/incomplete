static inline struct kvm_vmx *to_kvm_vmx(struct kvm *kvm)
{
	return container_of(kvm, struct kvm_vmx, kvm);
}
