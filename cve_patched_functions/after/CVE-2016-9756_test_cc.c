static __always_inline u8 test_cc(unsigned int condition, unsigned long flags)
{
	u8 rc;
	void (*fop)(void) = (void *)em_setcc + 4 * (condition & 0xf);

	flags = (flags & EFLAGS_MASK) | X86_EFLAGS_IF;
	asm("push %[flags]; popf; call *%[fastop]"
	    : "=a"(rc) : [fastop]"r"(fop), [flags]"r"(flags));
	return rc;
}
