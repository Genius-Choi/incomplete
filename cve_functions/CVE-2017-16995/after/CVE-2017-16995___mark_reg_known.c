static void __mark_reg_known(struct bpf_reg_state *reg, u64 imm)
{
	reg->id = 0;
	reg->var_off = tnum_const(imm);
	reg->smin_value = (s64)imm;
	reg->smax_value = (s64)imm;
	reg->umin_value = imm;
	reg->umax_value = imm;
}
