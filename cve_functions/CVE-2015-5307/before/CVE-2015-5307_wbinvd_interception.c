static int wbinvd_interception(struct vcpu_svm *svm)
{
	kvm_emulate_wbinvd(&svm->vcpu);
	return 1;
}
