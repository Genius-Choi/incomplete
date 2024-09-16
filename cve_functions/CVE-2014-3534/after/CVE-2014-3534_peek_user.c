peek_user(struct task_struct *child, addr_t addr, addr_t data)
{
	addr_t tmp, mask;

	/*
	 * Stupid gdb peeks/pokes the access registers in 64 bit with
	 * an alignment of 4. Programmers from hell...
	 */
	mask = __ADDR_MASK;
#ifdef CONFIG_64BIT
	if (addr >= (addr_t) &((struct user *) NULL)->regs.acrs &&
	    addr < (addr_t) &((struct user *) NULL)->regs.orig_gpr2)
		mask = 3;
#endif
	if ((addr & mask) || addr > sizeof(struct user) - __ADDR_MASK)
		return -EIO;

	tmp = __peek_user(child, addr);
	return put_user(tmp, (addr_t __user *) data);
}
