SYSCALL_DEFINE5(clone, unsigned long, clone_flags, unsigned long, newsp,
		 int __user *, parent_tidptr,
		 int, tls_val,
		 int __user *, child_tidptr)
#elif defined(CONFIG_CLONE_BACKWARDS2)
SYSCALL_DEFINE5(clone, unsigned long, newsp, unsigned long, clone_flags,
		 int __user *, parent_tidptr,
		 int __user *, child_tidptr,
		 int, tls_val)
#else
SYSCALL_DEFINE5(clone, unsigned long, clone_flags, unsigned long, newsp,
		 int __user *, parent_tidptr,
		 int __user *, child_tidptr,
		 int, tls_val)
#endif
{
	long ret = do_fork(clone_flags, newsp, 0, parent_tidptr, child_tidptr);
	asmlinkage_protect(5, ret, clone_flags, newsp,
			parent_tidptr, child_tidptr, tls_val);
	return ret;
}
