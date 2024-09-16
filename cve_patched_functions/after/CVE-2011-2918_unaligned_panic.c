static void __used unaligned_panic(char *str, struct pt_regs *regs)
{
	die_if_kernel(str, regs);
}
