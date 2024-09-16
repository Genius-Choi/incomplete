static int vmx_pre_leave_smm(struct kvm_vcpu *vcpu, u64 smbase)
{
	struct vcpu_vmx *vmx = to_vmx(vcpu);
	int ret;

	if (vmx->nested.smm.vmxon) {
		vmx->nested.vmxon = true;
		vmx->nested.smm.vmxon = false;
	}

	if (vmx->nested.smm.guest_mode) {
		vcpu->arch.hflags &= ~HF_SMM_MASK;
		ret = enter_vmx_non_root_mode(vcpu);
		vcpu->arch.hflags |= HF_SMM_MASK;
		if (ret)
			return ret;

		vmx->nested.smm.guest_mode = false;
	}
	return 0;
}
