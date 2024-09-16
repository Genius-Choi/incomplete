static int do_sock_sendmsg(struct socket *sock, struct msghdr *msg,
			   size_t size, bool nosec)
{
	struct kiocb iocb;
	int ret;

	init_sync_kiocb(&iocb, NULL);
	ret = nosec ? __sock_sendmsg_nosec(&iocb, sock, msg, size) :
		      __sock_sendmsg(&iocb, sock, msg, size);
	if (-EIOCBQUEUED == ret)
		ret = wait_on_sync_kiocb(&iocb);
	return ret;
}
