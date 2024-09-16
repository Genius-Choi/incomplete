static bool check_seg_overrides(struct insn *insn, int regoff)
{
	if (regoff == offsetof(struct pt_regs, di) && is_string_insn(insn))
		return false;

	return true;
}
