SYSCALL_DEFINE4(sendmmsg, int, fd, struct mmsghdr __user *, mmsg,
		unsigned int, vlen, unsigned int, flags)
{
	if (flags & MSG_CMSG_COMPAT)
		return -EINVAL;
	return __sys_sendmmsg(fd, mmsg, vlen, flags);
}
