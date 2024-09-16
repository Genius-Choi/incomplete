static int iucv_sock_getname(struct socket *sock, struct sockaddr *addr,
			     int *len, int peer)
{
	struct sockaddr_iucv *siucv = (struct sockaddr_iucv *) addr;
	struct sock *sk = sock->sk;
	struct iucv_sock *iucv = iucv_sk(sk);

	addr->sa_family = AF_IUCV;
	*len = sizeof(struct sockaddr_iucv);

	if (peer) {
		memcpy(siucv->siucv_user_id, iucv->dst_user_id, 8);
		memcpy(siucv->siucv_name, iucv->dst_name, 8);
	} else {
		memcpy(siucv->siucv_user_id, iucv->src_user_id, 8);
		memcpy(siucv->siucv_name, iucv->src_name, 8);
	}
	memset(&siucv->siucv_port, 0, sizeof(siucv->siucv_port));
	memset(&siucv->siucv_addr, 0, sizeof(siucv->siucv_addr));
	memset(&siucv->siucv_nodeid, 0, sizeof(siucv->siucv_nodeid));

	return 0;
}
