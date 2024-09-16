asmlinkage void do_exception_error(unsigned long r4, unsigned long r5,
				   unsigned long r6, unsigned long r7,
				   struct pt_regs __regs)
{
	struct pt_regs *regs = RELOC_HIDE(&__regs, 0);
	long ex;

	ex = lookup_exception_vector();
	die_if_kernel("exception", regs, ex);
}
