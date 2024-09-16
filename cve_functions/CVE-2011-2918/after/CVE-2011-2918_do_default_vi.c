static asmlinkage void do_default_vi(void)
{
	show_regs(get_irq_regs());
	panic("Caught unexpected vectored interrupt.");
}
