static void reset_pmcr(struct kvm_vcpu *vcpu, const struct sys_reg_desc *r)
{
	u64 pmcr, val;

	pmcr = read_sysreg(pmcr_el0);
	/*
	 * Writable bits of PMCR_EL0 (ARMV8_PMU_PMCR_MASK) are reset to UNKNOWN
	 * except PMCR.E resetting to zero.
	 */
	val = ((pmcr & ~ARMV8_PMU_PMCR_MASK)
	       | (ARMV8_PMU_PMCR_MASK & 0xdecafbad)) & (~ARMV8_PMU_PMCR_E);
	vcpu_sys_reg(vcpu, PMCR_EL0) = val;
}
