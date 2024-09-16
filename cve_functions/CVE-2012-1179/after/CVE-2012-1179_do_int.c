static void do_int(struct kernel_vm86_regs *regs, int i,
    unsigned char __user *ssp, unsigned short sp)
{
	unsigned long __user *intr_ptr;
	unsigned long segoffs;

	if (regs->pt.cs == BIOSSEG)
		goto cannot_handle;
	if (is_revectored(i, &KVM86->int_revectored))
		goto cannot_handle;
	if (i == 0x21 && is_revectored(AH(regs), &KVM86->int21_revectored))
		goto cannot_handle;
	intr_ptr = (unsigned long __user *) (i << 2);
	if (get_user(segoffs, intr_ptr))
		goto cannot_handle;
	if ((segoffs >> 16) == BIOSSEG)
		goto cannot_handle;
	pushw(ssp, sp, get_vflags(regs), cannot_handle);
	pushw(ssp, sp, regs->pt.cs, cannot_handle);
	pushw(ssp, sp, IP(regs), cannot_handle);
	regs->pt.cs = segoffs >> 16;
	SP(regs) -= 6;
	IP(regs) = segoffs & 0xffff;
	clear_TF(regs);
	clear_IF(regs);
	clear_AC(regs);
	return;

cannot_handle:
	return_to_32bit(regs, VM86_INTx + (i << 8));
}
