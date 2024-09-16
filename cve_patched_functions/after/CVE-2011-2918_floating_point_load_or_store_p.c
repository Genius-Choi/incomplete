static inline int floating_point_load_or_store_p(unsigned int insn)
{
	return (insn >> 24) & 1;
}
