static inline bool is_exception_n(u32 intr_info, u8 vector)
{
	return (intr_info & (INTR_INFO_INTR_TYPE_MASK | INTR_INFO_VECTOR_MASK |
			     INTR_INFO_VALID_MASK)) ==
		(INTR_TYPE_HARD_EXCEPTION | vector | INTR_INFO_VALID_MASK);
}
