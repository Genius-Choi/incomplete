asmlinkage void do_tr(struct pt_regs *regs)
{
	unsigned int opcode, tcode = 0;

	if (__get_user(opcode, (unsigned int __user *) exception_epc(regs)))
		goto out_sigsegv;

	/* Immediate versions don't provide a code.  */
	if (!(opcode & OPCODE))
		tcode = ((opcode >> 6) & ((1 << 10) - 1));

	do_trap_or_bp(regs, tcode, "Trap");
	return;

out_sigsegv:
	force_sig(SIGSEGV, current);
}
