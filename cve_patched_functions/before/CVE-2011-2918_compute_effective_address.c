unsigned long compute_effective_address(struct pt_regs *regs,
					unsigned int insn, unsigned int rd)
{
	unsigned int rs1 = (insn >> 14) & 0x1f;
	unsigned int rs2 = insn & 0x1f;
	int from_kernel = (regs->tstate & TSTATE_PRIV) != 0;

	if (insn & 0x2000) {
		maybe_flush_windows(rs1, 0, rd, from_kernel);
		return (fetch_reg(rs1, regs) + sign_extend_imm13(insn));
	} else {
		maybe_flush_windows(rs1, rs2, rd, from_kernel);
		return (fetch_reg(rs1, regs) + fetch_reg(rs2, regs));
	}
}
