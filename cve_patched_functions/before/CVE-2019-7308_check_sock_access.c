static int check_sock_access(struct bpf_verifier_env *env, u32 regno, int off,
			     int size, enum bpf_access_type t)
{
	struct bpf_reg_state *regs = cur_regs(env);
	struct bpf_reg_state *reg = &regs[regno];
	struct bpf_insn_access_aux info;

	if (reg->smin_value < 0) {
		verbose(env, "R%d min value is negative, either use unsigned index or do a if (index >=0) check.\n",
			regno);
		return -EACCES;
	}

	if (!bpf_sock_is_valid_access(off, size, t, &info)) {
		verbose(env, "invalid bpf_sock access off=%d size=%d\n",
			off, size);
		return -EACCES;
	}

	return 0;
}
