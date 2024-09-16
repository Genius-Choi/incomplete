static bool reg_is_refcounted_or_null(const struct bpf_reg_state *reg)
{
	return type_is_refcounted_or_null(reg->type);
}
