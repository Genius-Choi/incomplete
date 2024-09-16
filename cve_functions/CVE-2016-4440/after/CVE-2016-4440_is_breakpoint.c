static inline bool is_breakpoint(u32 intr_info)
{
	return is_exception_n(intr_info, BP_VECTOR);
}
