static inline int decode_signedness(unsigned int insn)
{
	return (insn & 0x400000);
}
