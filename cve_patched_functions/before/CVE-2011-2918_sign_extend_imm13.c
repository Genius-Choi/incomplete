static inline long sign_extend_imm13(long imm)
{
	return imm << 51 >> 51;
}
