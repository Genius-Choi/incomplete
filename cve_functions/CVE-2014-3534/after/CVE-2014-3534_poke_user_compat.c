static int poke_user_compat(struct task_struct *child,
			    addr_t addr, addr_t data)
{
	if (!is_compat_task() || (addr & 3) ||
	    addr > sizeof(struct compat_user) - 3)
		return -EIO;

	return __poke_user_compat(child, addr, data);
}
