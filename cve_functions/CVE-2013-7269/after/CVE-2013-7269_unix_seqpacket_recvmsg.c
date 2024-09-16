static int unix_seqpacket_recvmsg(struct kiocb *iocb, struct socket *sock,
			      struct msghdr *msg, size_t size,
			      int flags)
{
	struct sock *sk = sock->sk;

	if (sk->sk_state != TCP_ESTABLISHED)
		return -ENOTCONN;

	return unix_dgram_recvmsg(iocb, sock, msg, size, flags);
}
