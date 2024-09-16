static int vmmcall_interception(struct vcpu_svm *svm)
{
	svm->next_rip = kvm_rip_read(&svm->vcpu) + 3;
	kvm_emulate_hypercall(&svm->vcpu);
	return 1;
}
