static void edge(struct pt_regs *regs, unsigned int insn, unsigned int opf)
{
	unsigned long orig_rs1, rs1, orig_rs2, rs2, rd_val;
	u16 left, right;

	maybe_flush_windows(RS1(insn), RS2(insn), RD(insn), 0);
	orig_rs1 = rs1 = fetch_reg(RS1(insn), regs);
	orig_rs2 = rs2 = fetch_reg(RS2(insn), regs);

	if (test_thread_flag(TIF_32BIT)) {
		rs1 = rs1 & 0xffffffff;
		rs2 = rs2 & 0xffffffff;
	}
	switch (opf) {
	default:
	case EDGE8_OPF:
	case EDGE8N_OPF:
		left = edge8_tab[rs1 & 0x7].left;
		right = edge8_tab[rs2 & 0x7].right;
		break;
	case EDGE8L_OPF:
	case EDGE8LN_OPF:
		left = edge8_tab_l[rs1 & 0x7].left;
		right = edge8_tab_l[rs2 & 0x7].right;
		break;

	case EDGE16_OPF:
	case EDGE16N_OPF:
		left = edge16_tab[(rs1 >> 1) & 0x3].left;
		right = edge16_tab[(rs2 >> 1) & 0x3].right;
		break;

	case EDGE16L_OPF:
	case EDGE16LN_OPF:
		left = edge16_tab_l[(rs1 >> 1) & 0x3].left;
		right = edge16_tab_l[(rs2 >> 1) & 0x3].right;
		break;

	case EDGE32_OPF:
	case EDGE32N_OPF:
		left = edge32_tab[(rs1 >> 2) & 0x1].left;
		right = edge32_tab[(rs2 >> 2) & 0x1].right;
		break;

	case EDGE32L_OPF:
	case EDGE32LN_OPF:
		left = edge32_tab_l[(rs1 >> 2) & 0x1].left;
		right = edge32_tab_l[(rs2 >> 2) & 0x1].right;
		break;
	}

	if ((rs1 & ~0x7UL) == (rs2 & ~0x7UL))
		rd_val = right & left;
	else
		rd_val = left;

	store_reg(regs, rd_val, RD(insn));

	switch (opf) {
	case EDGE8_OPF:
	case EDGE8L_OPF:
	case EDGE16_OPF:
	case EDGE16L_OPF:
	case EDGE32_OPF:
	case EDGE32L_OPF: {
		unsigned long ccr, tstate;

		__asm__ __volatile__("subcc	%1, %2, %%g0\n\t"
				     "rd	%%ccr, %0"
				     : "=r" (ccr)
				     : "r" (orig_rs1), "r" (orig_rs2)
				     : "cc");
		tstate = regs->tstate & ~(TSTATE_XCC | TSTATE_ICC);
		regs->tstate = tstate | (ccr << 32UL);
	}
	}
}
