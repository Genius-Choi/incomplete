static struct kvm *vmx_vm_alloc(void)
{
	struct kvm_vmx *kvm_vmx = vzalloc(sizeof(struct kvm_vmx));
	return &kvm_vmx->kvm;
}
