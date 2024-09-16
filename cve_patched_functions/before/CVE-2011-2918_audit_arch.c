static inline int audit_arch(void)
{
	int arch = EM_SH;

#ifdef CONFIG_CPU_LITTLE_ENDIAN
	arch |= __AUDIT_ARCH_LE;
#endif

	return arch;
}
