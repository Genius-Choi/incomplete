static inline int __sock_recvmsg_nosec(struct kiocb *iocb, struct socket *sock,
				       struct msghdr *msg, size_t size, int flags)
{
	return sock->ops->recvmsg(iocb, sock, msg, size, flags);
}
