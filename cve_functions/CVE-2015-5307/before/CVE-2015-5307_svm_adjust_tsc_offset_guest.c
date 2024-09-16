static void svm_adjust_tsc_offset_guest(struct kvm_vcpu *vcpu, s64 adjustment)
{
	struct vcpu_svm *svm = to_svm(vcpu);

	svm->vmcb->control.tsc_offset += adjustment;
	if (is_guest_mode(vcpu))
		svm->nested.hsave->control.tsc_offset += adjustment;
	else
		trace_kvm_write_tsc_offset(vcpu->vcpu_id,
				     svm->vmcb->control.tsc_offset - adjustment,
				     svm->vmcb->control.tsc_offset);

	mark_dirty(svm->vmcb, VMCB_INTERCEPTS);
}
