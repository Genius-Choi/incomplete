int kvm_arch_vcpu_runnable(struct kvm_vcpu *v)
{
	return !!v->arch.irq_lines || kvm_vgic_vcpu_pending_irq(v);
}
