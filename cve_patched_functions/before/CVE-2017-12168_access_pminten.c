static bool access_pminten(struct kvm_vcpu *vcpu, struct sys_reg_params *p,
			   const struct sys_reg_desc *r)
{
	u64 mask = kvm_pmu_valid_counter_mask(vcpu);

	if (!kvm_arm_pmu_v3_ready(vcpu))
		return trap_raz_wi(vcpu, p, r);

	if (!vcpu_mode_priv(vcpu))
		return false;

	if (p->is_write) {
		u64 val = p->regval & mask;

		if (r->Op2 & 0x1)
			/* accessing PMINTENSET_EL1 */
			vcpu_sys_reg(vcpu, PMINTENSET_EL1) |= val;
		else
			/* accessing PMINTENCLR_EL1 */
			vcpu_sys_reg(vcpu, PMINTENSET_EL1) &= ~val;
	} else {
		p->regval = vcpu_sys_reg(vcpu, PMINTENSET_EL1) & mask;
	}

	return true;
}
