void kvm_inject_apic_timer_irqs(struct kvm_vcpu *vcpu)
{
	struct kvm_lapic *apic = vcpu->arch.apic;

	if (!kvm_vcpu_has_lapic(vcpu))
		return;

	if (atomic_read(&apic->lapic_timer.pending) > 0) {
		kvm_apic_local_deliver(apic, APIC_LVTT);
		atomic_set(&apic->lapic_timer.pending, 0);
	}
}
