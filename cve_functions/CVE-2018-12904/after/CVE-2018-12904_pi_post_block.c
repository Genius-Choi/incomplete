static void pi_post_block(struct kvm_vcpu *vcpu)
{
	if (vcpu->pre_pcpu == -1)
		return;

	WARN_ON(irqs_disabled());
	local_irq_disable();
	__pi_post_block(vcpu);
	local_irq_enable();
}
