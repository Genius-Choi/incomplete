static inline bool is_page_fault(u32 intr_info)
{
	return is_exception_n(intr_info, PF_VECTOR);
}
