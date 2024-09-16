static int opcmov(RAsm *a, ut8 *data, const Opcode *op) {
	int l = 0;
	int mod_byte = 0;
	int offset = 0;

	if (op->operands[0].type & OT_MEMORY ||
	    op->operands[1].type & OT_CONSTANT) {
		return -1;
	}

	data[l++] = 0x0f;
	char *cmov = op->mnemonic + 4;
	if (!strcmp (cmov, "o")) {
		data[l++] = 0x40;
	} else if (!strcmp (cmov, "no")) {
		data [l++] = 0x41;
	} else if (!strcmp (cmov, "b") ||
	           !strcmp (cmov, "c") ||
	           !strcmp (cmov, "nae")) {
		data [l++] = 0x42;
	} else if (!strcmp (cmov, "ae") ||
	           !strcmp (cmov, "nb") ||
		   !strcmp (cmov, "nc")) {
		data [l++] = 0x43;
	} else if (!strcmp (cmov, "e") ||
                   !strcmp (cmov, "z")) {
		data [l++] = 0x44;
	} else if (!strcmp (cmov, "ne") ||
	           !strcmp (cmov, "nz")) {
		data [l++] = 0x45;
        } else if (!strcmp (cmov, "be") ||
	           !strcmp (cmov, "na")) {
		data [l++] = 0x46;
        } else if (!strcmp (cmov, "a") ||
	           !strcmp (cmov, "nbe")) {
		data [l++] = 0x47;
	} else if (!strcmp (cmov, "s")) {
		data [l++] = 0x48;
        } else if (!strcmp (cmov, "ns")) {
		data [l++] = 0x49;
        } else if (!strcmp (cmov, "p") ||
	           !strcmp (cmov, "pe")) {
		data [l++] = 0x4a;
        } else if (!strcmp (cmov, "np") ||
	           !strcmp (cmov, "po")) {
		data [l++] = 0x4b;
        } else if (!strcmp (cmov, "l") ||
	           !strcmp (cmov, "nge")) {
		data [l++] = 0x4c;
        } else if (!strcmp (cmov, "ge") ||
	           !strcmp (cmov, "nl")) {
		data [l++] = 0x4d;
        } else if (!strcmp (cmov, "le") ||
	           !strcmp (cmov, "ng")) {
		data [l++] = 0x4e;
        } else if (!strcmp (cmov, "g") ||
	           !strcmp (cmov, "nle")) {
		data [l++] = 0x4f;
        }

	if (op->operands[0].type & OT_REGALL) {
		if (op->operands[1].type & OT_MEMORY) {
			if (op->operands[1].scale[0] > 1) {
				if (op->operands[1].regs[1] != X86R_UNDEFINED) {
					data[l++] = op->operands[0].reg << 3 | 4;
					data[l++] = getsib (op->operands[1].scale[0]) << 6 |
                                                            op->operands[1].regs[0] << 3 |
                                                            op->operands[1].regs[1];
					return l;
				}
				offset = op->operands[1].offset * op->operands[1].offset_sign;

				if (op->operands[1].scale[0] == 2 && offset) {
					data[l++] = 0x40 | op->operands[0].reg << 3 | 4; // 4 = SIB
				} else {
					data[l++] = op->operands[0].reg << 3 | 4; // 4 = SIB
				}


				if (op->operands[1].scale[0] == 2) {
					data[l++] = op->operands[1].regs[0] << 3 | op->operands[1].regs[0];

				} else {
					data[l++] = getsib (op->operands[1].scale[0]) << 6 |
                                                            op->operands[1].regs[0] << 3 | 5;
				}

				if (offset) {
					data[l++] = offset;
					if (offset < ST8_MIN || offset > ST8_MAX) {
						data[l++] = offset >> 8;
						data[l++] = offset >> 16;
						data[l++] = offset >> 24;
					}
				}
				return l;
			}
			if (op->operands[1].regs[1] != X86R_UNDEFINED) {
				data[l++] = op->operands[0].reg << 3 | 4;
				data[l++] = op->operands[1].regs[1] << 3 | op->operands[1].regs[0];
				return l;
			}

			offset = op->operands[1].offset * op->operands[1].offset_sign;
			if (op->operands[1].offset || op->operands[1].regs[0] == X86R_EBP) {
				mod_byte = 1;
			}
			if (offset < ST8_MIN || offset > ST8_MAX) {
				mod_byte = 2;
			}

			data[l++] = mod_byte << 6 | op->operands[0].reg << 3 | op->operands[1].regs[0];

			if (mod_byte) {
				data[l++] = offset;
				if (mod_byte == 2) {
					data[l++] = offset >> 8;
					data[l++] = offset >> 16;
					data[l++] = offset >> 24;
				}
			}
		} else {
			data[l++] = 0xc0 | op->operands[0].reg << 3 | op->operands[1].reg;
		}
	}

	return l;
}
