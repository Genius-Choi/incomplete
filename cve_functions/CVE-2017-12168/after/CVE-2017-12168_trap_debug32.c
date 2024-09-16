static bool trap_debug32(struct kvm_vcpu *vcpu,
			 struct sys_reg_params *p,
			 const struct sys_reg_desc *r)
{
	if (p->is_write) {
		vcpu_cp14(vcpu, r->reg) = p->regval;
		vcpu->arch.debug_flags |= KVM_ARM64_DEBUG_DIRTY;
	} else {
		p->regval = vcpu_cp14(vcpu, r->reg);
	}

	return true;
}
