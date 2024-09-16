static void check_stack_aligned(unsigned long sp)
{
	if (sp & 0x7UL)
		force_sig(SIGILL, current);
}
