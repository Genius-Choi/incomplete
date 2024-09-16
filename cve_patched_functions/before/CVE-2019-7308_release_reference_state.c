static int release_reference_state(struct bpf_verifier_env *env, int ptr_id)
{
	struct bpf_func_state *state = cur_func(env);
	int err;

	err = __release_reference_state(state, ptr_id);
	if (WARN_ON_ONCE(err != 0))
		verbose(env, "verifier internal error: can't release reference\n");
	return err;
}
