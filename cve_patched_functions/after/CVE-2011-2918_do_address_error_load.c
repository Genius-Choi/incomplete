asmlinkage void do_address_error_load(unsigned long error_code, struct pt_regs *regs)
{
	if (misaligned_fixup(regs) < 0) {
		do_unhandled_exception(7, SIGSEGV, "address error(load)",
				"do_address_error_load",
				error_code, regs, current);
	}
	return;
}
