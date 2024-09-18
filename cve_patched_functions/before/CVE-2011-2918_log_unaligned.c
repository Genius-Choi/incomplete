static void log_unaligned(struct pt_regs *regs)
{
	static DEFINE_RATELIMIT_STATE(ratelimit, 5 * HZ, 5);

	if (__ratelimit(&ratelimit)) {
		printk("Kernel unaligned access at TPC[%lx] %pS\n",
		       regs->tpc, (void *) regs->tpc);
	}
}
