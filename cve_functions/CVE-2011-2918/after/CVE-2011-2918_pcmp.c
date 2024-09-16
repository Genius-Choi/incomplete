static void pcmp(struct pt_regs *regs, unsigned int insn, unsigned int opf)
{
	struct fpustate *f = FPUSTATE;
	unsigned long rs1, rs2, rd_val, i;

	rs1 = fpd_regval(f, RS1(insn));
	rs2 = fpd_regval(f, RS2(insn));

	rd_val = 0;

	switch (opf) {
	case FCMPGT16_OPF:
		for (i = 0; i < 4; i++) {
			s16 a = (rs1 >> (i * 16)) & 0xffff;
			s16 b = (rs2 >> (i * 16)) & 0xffff;

			if (a > b)
				rd_val |= 1 << i;
		}
		break;

	case FCMPGT32_OPF:
		for (i = 0; i < 2; i++) {
			s32 a = (rs1 >> (i * 32)) & 0xffff;
			s32 b = (rs2 >> (i * 32)) & 0xffff;

			if (a > b)
				rd_val |= 1 << i;
		}
		break;

	case FCMPLE16_OPF:
		for (i = 0; i < 4; i++) {
			s16 a = (rs1 >> (i * 16)) & 0xffff;
			s16 b = (rs2 >> (i * 16)) & 0xffff;

			if (a <= b)
				rd_val |= 1 << i;
		}
		break;

	case FCMPLE32_OPF:
		for (i = 0; i < 2; i++) {
			s32 a = (rs1 >> (i * 32)) & 0xffff;
			s32 b = (rs2 >> (i * 32)) & 0xffff;

			if (a <= b)
				rd_val |= 1 << i;
		}
		break;

	case FCMPNE16_OPF:
		for (i = 0; i < 4; i++) {
			s16 a = (rs1 >> (i * 16)) & 0xffff;
			s16 b = (rs2 >> (i * 16)) & 0xffff;

			if (a != b)
				rd_val |= 1 << i;
		}
		break;

	case FCMPNE32_OPF:
		for (i = 0; i < 2; i++) {
			s32 a = (rs1 >> (i * 32)) & 0xffff;
			s32 b = (rs2 >> (i * 32)) & 0xffff;

			if (a != b)
				rd_val |= 1 << i;
		}
		break;

	case FCMPEQ16_OPF:
		for (i = 0; i < 4; i++) {
			s16 a = (rs1 >> (i * 16)) & 0xffff;
			s16 b = (rs2 >> (i * 16)) & 0xffff;

			if (a == b)
				rd_val |= 1 << i;
		}
		break;

	case FCMPEQ32_OPF:
		for (i = 0; i < 2; i++) {
			s32 a = (rs1 >> (i * 32)) & 0xffff;
			s32 b = (rs2 >> (i * 32)) & 0xffff;

			if (a == b)
				rd_val |= 1 << i;
		}
		break;
	}

	maybe_flush_windows(0, 0, RD(insn), 0);
	store_reg(regs, rd_val, RD(insn));
}
