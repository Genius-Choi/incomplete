static inline int __sock_sendmsg_nosec(struct kiocb *iocb, struct socket *sock,
				       struct msghdr *msg, size_t size)
{
	return sock->ops->sendmsg(iocb, sock, msg, size);
}
