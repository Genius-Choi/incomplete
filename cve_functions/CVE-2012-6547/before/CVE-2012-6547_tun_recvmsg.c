static int tun_recvmsg(struct kiocb *iocb, struct socket *sock,
		       struct msghdr *m, size_t total_len,
		       int flags)
{
	struct tun_struct *tun = container_of(sock, struct tun_struct, socket);
	int ret;
	if (flags & ~(MSG_DONTWAIT|MSG_TRUNC))
		return -EINVAL;
	ret = tun_do_read(tun, iocb, m->msg_iov, total_len,
			  flags & MSG_DONTWAIT);
	if (ret > total_len) {
		m->msg_flags |= MSG_TRUNC;
		ret = flags & MSG_TRUNC ? ret : total_len;
	}
	return ret;
}
