static int copy_verifier_state(struct bpf_verifier_state *dst,
			       const struct bpf_verifier_state *src)
{
	int err;

	err = realloc_verifier_state(dst, src->allocated_stack, false);
	if (err)
		return err;
	memcpy(dst, src, offsetof(struct bpf_verifier_state, allocated_stack));
	return copy_stack_state(dst, src);
}
