static void mark_ptr_or_null_regs(struct bpf_verifier_state *vstate, u32 regno,
				  bool is_null)
{
	struct bpf_func_state *state = vstate->frame[vstate->curframe];
	struct bpf_reg_state *reg, *regs = state->regs;
	u32 id = regs[regno].id;
	int i, j;

	if (reg_is_refcounted_or_null(&regs[regno]) && is_null)
		__release_reference_state(state, id);

	for (i = 0; i < MAX_BPF_REG; i++)
		mark_ptr_or_null_reg(state, &regs[i], id, is_null);

	for (j = 0; j <= vstate->curframe; j++) {
		state = vstate->frame[j];
		bpf_for_each_spilled_reg(i, state, reg) {
			if (!reg)
				continue;
			mark_ptr_or_null_reg(state, reg, id, is_null);
		}
	}
}
