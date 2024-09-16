void window_underflow_fault(unsigned long sp)
{
	if(((sp + 0x38) & PAGE_MASK) != (sp & PAGE_MASK))
		force_user_fault(sp + 0x38, 0);
	force_user_fault(sp, 0);

	check_stack_aligned(sp);
}
