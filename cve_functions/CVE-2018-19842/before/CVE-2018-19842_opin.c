static int opin(RAsm *a, ut8 *data, const Opcode *op) {
	int l = 0;
	st32 immediate = 0;
	if (op->operands[1].reg == X86R_DX) {
		if (op->operands[0].reg == X86R_AL &&
			op->operands[0].type & OT_BYTE) {
			data[l++] = 0xec;
			return l;
		}
		if (op->operands[0].reg == X86R_AX &&
			op->operands[0].type & OT_WORD) {
			data[l++] = 0x66;
			data[l++] = 0xed;
			return l;
		}
		if (op->operands[0].reg == X86R_EAX &&
			op->operands[0].type & OT_DWORD) {
			data[l++] = 0xed;
			return l;
		}
	} else if (op->operands[1].type & OT_CONSTANT) {
		immediate = op->operands[1].immediate * op->operands[1].sign;
		if (immediate > 255 || immediate < -128) {
			return -1;
		}
		if (op->operands[0].reg == X86R_AL &&
			op->operands[0].type & OT_BYTE) {
			data[l++] = 0xe4;
		} else if (op->operands[0].reg == X86R_AX &&
				   op->operands[0].type & OT_BYTE) {
			data[l++] = 0x66;
			data[l++] = 0xe5;
		} else if (op->operands[0].reg == X86R_EAX &&
				   op->operands[0].type & OT_DWORD) {
			data[l++] = 0xe5;
		}
		data[l++] = immediate;
	}
	return l;
}
