static void enable_nmi_window(struct kvm_vcpu *vcpu)
{
	if (vmcs_read32(GUEST_INTERRUPTIBILITY_INFO) & GUEST_INTR_STATE_STI) {
		enable_irq_window(vcpu);
		return;
	}

	vmcs_set_bits(CPU_BASED_VM_EXEC_CONTROL,
		      CPU_BASED_VIRTUAL_NMI_PENDING);
}
