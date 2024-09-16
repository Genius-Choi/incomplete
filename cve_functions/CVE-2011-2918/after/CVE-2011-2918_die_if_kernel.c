static inline void die_if_kernel(const char *str, struct pt_regs *regs,
				 long err)
{
	if (!user_mode(regs))
		die(str, regs, err);
}
