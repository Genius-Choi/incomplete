static int peek_user_compat(struct task_struct *child,
			    addr_t addr, addr_t data)
{
	__u32 tmp;

	if (!is_compat_task() || (addr & 3) || addr > sizeof(struct user) - 3)
		return -EIO;

	tmp = __peek_user_compat(child, addr);
	return put_user(tmp, (__u32 __user *) data);
}
