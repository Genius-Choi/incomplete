static bool reg_is_refcounted(const struct bpf_reg_state *reg)
{
	return type_is_refcounted(reg->type);
}
