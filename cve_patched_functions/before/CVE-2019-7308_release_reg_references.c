static void release_reg_references(struct bpf_verifier_env *env,
				   struct bpf_func_state *state, int id)
{
	struct bpf_reg_state *regs = state->regs, *reg;
	int i;

	for (i = 0; i < MAX_BPF_REG; i++)
		if (regs[i].id == id)
			mark_reg_unknown(env, regs, i);

	bpf_for_each_spilled_reg(i, state, reg) {
		if (!reg)
			continue;
		if (reg_is_refcounted(reg) && reg->id == id)
			__mark_reg_unknown(reg);
	}
}
