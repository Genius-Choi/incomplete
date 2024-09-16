static int emulate_cp(struct kvm_vcpu *vcpu,
		      struct sys_reg_params *params,
		      const struct sys_reg_desc *table,
		      size_t num)
{
	const struct sys_reg_desc *r;

	if (!table)
		return -1;	/* Not handled */

	r = find_reg(params, table, num);

	if (r) {
		/*
		 * Not having an accessor means that we have
		 * configured a trap that we don't know how to
		 * handle. This certainly qualifies as a gross bug
		 * that should be fixed right away.
		 */
		BUG_ON(!r->access);

		if (likely(r->access(vcpu, params, r))) {
			/* Skip instruction, since it was emulated */
			kvm_skip_instr(vcpu, kvm_vcpu_trap_il_is32bit(vcpu));
			/* Handled */
			return 0;
		}
	}

	/* Not handled */
	return -1;
}
