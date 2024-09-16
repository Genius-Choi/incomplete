static void free_verifier_state(struct bpf_verifier_state *state,
				bool free_self)
{
	kfree(state->stack);
	if (free_self)
		kfree(state);
}
