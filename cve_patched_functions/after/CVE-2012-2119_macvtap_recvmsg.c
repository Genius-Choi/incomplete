static int macvtap_recvmsg(struct kiocb *iocb, struct socket *sock,
			   struct msghdr *m, size_t total_len,
			   int flags)
{
	struct macvtap_queue *q = container_of(sock, struct macvtap_queue, sock);
	int ret;
	if (flags & ~(MSG_DONTWAIT|MSG_TRUNC))
		return -EINVAL;
	ret = macvtap_do_read(q, iocb, m->msg_iov, total_len,
			  flags & MSG_DONTWAIT);
	if (ret > total_len) {
		m->msg_flags |= MSG_TRUNC;
		ret = flags & MSG_TRUNC ? ret : total_len;
	}
	return ret;
}
