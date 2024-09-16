static inline bool is_debug(u32 intr_info)
{
	return is_exception_n(intr_info, DB_VECTOR);
}
