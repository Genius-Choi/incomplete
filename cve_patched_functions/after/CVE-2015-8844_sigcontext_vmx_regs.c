static elf_vrreg_t __user *sigcontext_vmx_regs(struct sigcontext __user *sc)
{
	return (elf_vrreg_t __user *) (((unsigned long)sc->vmx_reserve + 15) & ~0xful);
}
