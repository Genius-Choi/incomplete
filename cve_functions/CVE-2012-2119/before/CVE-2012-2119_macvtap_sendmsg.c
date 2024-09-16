static int macvtap_sendmsg(struct kiocb *iocb, struct socket *sock,
			   struct msghdr *m, size_t total_len)
{
	struct macvtap_queue *q = container_of(sock, struct macvtap_queue, sock);
	return macvtap_get_user(q, m, m->msg_iov, total_len, m->msg_iovlen,
			    m->msg_flags & MSG_DONTWAIT);
}
