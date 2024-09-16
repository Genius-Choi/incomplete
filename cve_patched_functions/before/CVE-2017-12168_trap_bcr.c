static bool trap_bcr(struct kvm_vcpu *vcpu,
		     struct sys_reg_params *p,
		     const struct sys_reg_desc *rd)
{
	u64 *dbg_reg = &vcpu->arch.vcpu_debug_state.dbg_bcr[rd->reg];

	if (p->is_write)
		reg_to_dbg(vcpu, p, dbg_reg);
	else
		dbg_to_reg(vcpu, p, dbg_reg);

	trace_trap_reg(__func__, rd->reg, p->is_write, *dbg_reg);

	return true;
}
