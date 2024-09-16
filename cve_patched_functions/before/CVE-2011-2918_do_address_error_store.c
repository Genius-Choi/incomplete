asmlinkage void do_address_error_store(unsigned long error_code, struct pt_regs *regs)
{
	if (misaligned_fixup(regs) < 0) {
		do_unhandled_exception(8, SIGSEGV, "address error(store)",
				"do_address_error_store",
				error_code, regs, current);
	}
	return;
}
