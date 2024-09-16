static int do_set_attach_filter(struct socket *sock, int level, int optname,
				char __user *optval, unsigned int optlen)
{
	struct compat_sock_fprog __user *fprog32 = (struct compat_sock_fprog __user *)optval;
	struct sock_fprog __user *kfprog = compat_alloc_user_space(sizeof(struct sock_fprog));
	compat_uptr_t ptr;
	u16 len;

	if (!access_ok(VERIFY_READ, fprog32, sizeof(*fprog32)) ||
	    !access_ok(VERIFY_WRITE, kfprog, sizeof(struct sock_fprog)) ||
	    __get_user(len, &fprog32->len) ||
	    __get_user(ptr, &fprog32->filter) ||
	    __put_user(len, &kfprog->len) ||
	    __put_user(compat_ptr(ptr), &kfprog->filter))
		return -EFAULT;

	return sock_setsockopt(sock, level, optname, (char __user *)kfprog,
			      sizeof(struct sock_fprog));
}
