static bool access_pmcnten(struct kvm_vcpu *vcpu, struct sys_reg_params *p,
			   const struct sys_reg_desc *r)
{
	u64 val, mask;

	if (!kvm_arm_pmu_v3_ready(vcpu))
		return trap_raz_wi(vcpu, p, r);

	if (pmu_access_el0_disabled(vcpu))
		return false;

	mask = kvm_pmu_valid_counter_mask(vcpu);
	if (p->is_write) {
		val = p->regval & mask;
		if (r->Op2 & 0x1) {
			/* accessing PMCNTENSET_EL0 */
			vcpu_sys_reg(vcpu, PMCNTENSET_EL0) |= val;
			kvm_pmu_enable_counter(vcpu, val);
		} else {
			/* accessing PMCNTENCLR_EL0 */
			vcpu_sys_reg(vcpu, PMCNTENSET_EL0) &= ~val;
			kvm_pmu_disable_counter(vcpu, val);
		}
	} else {
		p->regval = vcpu_sys_reg(vcpu, PMCNTENSET_EL0) & mask;
	}

	return true;
}
