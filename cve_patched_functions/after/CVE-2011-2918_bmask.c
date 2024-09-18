static void bmask(struct pt_regs *regs, unsigned int insn)
{
	unsigned long rs1, rs2, rd_val, gsr;

	maybe_flush_windows(RS1(insn), RS2(insn), RD(insn), 0);
	rs1 = fetch_reg(RS1(insn), regs);
	rs2 = fetch_reg(RS2(insn), regs);
	rd_val = rs1 + rs2;

	store_reg(regs, rd_val, RD(insn));

	gsr = current_thread_info()->gsr[0] & 0xffffffff;
	gsr |= rd_val << 32UL;
	current_thread_info()->gsr[0] = gsr;
}
