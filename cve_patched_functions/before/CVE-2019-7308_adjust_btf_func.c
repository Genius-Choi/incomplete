static void adjust_btf_func(struct bpf_verifier_env *env)
{
	int i;

	if (!env->prog->aux->func_info)
		return;

	for (i = 0; i < env->subprog_cnt; i++)
		env->prog->aux->func_info[i].insn_off = env->subprog_info[i].start;
}
