static int emulate_string_inst(struct pt_regs *regs, u32 instword)
{
	u8 rT = (instword >> 21) & 0x1f;
	u8 rA = (instword >> 16) & 0x1f;
	u8 NB_RB = (instword >> 11) & 0x1f;
	u32 num_bytes;
	unsigned long EA;
	int pos = 0;

	/* Early out if we are an invalid form of lswx */
	if ((instword & INST_STRING_MASK) == INST_LSWX)
		if ((rT == rA) || (rT == NB_RB))
			return -EINVAL;

	EA = (rA == 0) ? 0 : regs->gpr[rA];

	switch (instword & INST_STRING_MASK) {
		case INST_LSWX:
		case INST_STSWX:
			EA += NB_RB;
			num_bytes = regs->xer & 0x7f;
			break;
		case INST_LSWI:
		case INST_STSWI:
			num_bytes = (NB_RB == 0) ? 32 : NB_RB;
			break;
		default:
			return -EINVAL;
	}

	while (num_bytes != 0)
	{
		u8 val;
		u32 shift = 8 * (3 - (pos & 0x3));

		switch ((instword & INST_STRING_MASK)) {
			case INST_LSWX:
			case INST_LSWI:
				if (get_user(val, (u8 __user *)EA))
					return -EFAULT;
				/* first time updating this reg,
				 * zero it out */
				if (pos == 0)
					regs->gpr[rT] = 0;
				regs->gpr[rT] |= val << shift;
				break;
			case INST_STSWI:
			case INST_STSWX:
				val = regs->gpr[rT] >> shift;
				if (put_user(val, (u8 __user *)EA))
					return -EFAULT;
				break;
		}
		/* move EA to next address */
		EA += 1;
		num_bytes--;

		/* manage our position within the register */
		if (++pos == 4) {
			pos = 0;
			if (++rT == 32)
				rT = 0;
		}
	}

	return 0;
}
