static int ext_analyzer_insn_hook(struct bpf_verifier_env *env,
				  int insn_idx, int prev_insn_idx)
{
	if (env->dev_ops && env->dev_ops->insn_hook)
		return env->dev_ops->insn_hook(env, insn_idx, prev_insn_idx);

	return 0;
}
