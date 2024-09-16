static int release_reference(struct bpf_verifier_env *env,
			     struct bpf_call_arg_meta *meta)
{
	struct bpf_verifier_state *vstate = env->cur_state;
	int i;

	for (i = 0; i <= vstate->curframe; i++)
		release_reg_references(env, vstate->frame[i], meta->ptr_id);

	return release_reference_state(env, meta->ptr_id);
}
