static int vmx_get_msr_feature(struct kvm_msr_entry *msr)
{
	switch (msr->index) {
	case MSR_IA32_VMX_BASIC ... MSR_IA32_VMX_VMFUNC:
		if (!nested)
			return 1;
		return vmx_get_vmx_msr(&vmcs_config.nested, msr->index, &msr->data);
	default:
		return 1;
	}

	return 0;
}
