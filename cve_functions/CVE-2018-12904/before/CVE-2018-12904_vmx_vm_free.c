static void vmx_vm_free(struct kvm *kvm)
{
	vfree(to_kvm_vmx(kvm));
}
