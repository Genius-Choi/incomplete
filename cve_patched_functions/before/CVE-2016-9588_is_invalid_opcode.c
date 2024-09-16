static inline bool is_invalid_opcode(u32 intr_info)
{
	return is_exception_n(intr_info, UD_VECTOR);
}
