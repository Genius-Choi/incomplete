static int opbswap(RAsm *a, ut8 *data, const Opcode *op) {
	int l = 0;
	if (op->operands[0].type & OT_REGALL) {
		if (op->operands[0].reg == X86R_UNDEFINED) {
			return -1;
		}

		if (op->operands[0].type & OT_QWORD) {
			data[l++] = 0x48;
			data[l++] = 0x0f;
			data[l++] = 0xc8 + op->operands[0].reg;
		} else if (op->operands[0].type & OT_DWORD) {
			data[l++] = 0x0f;
			data[l++] = 0xc8 + op->operands[0].reg;
		} else {
			return -1;
		}
	}
	return l;
}
