static int auto_connect(struct socket *sock, struct tipc_msg *msg)
{
	struct tipc_sock *tsock = tipc_sk(sock->sk);
	struct tipc_port *p_ptr;

	tsock->peer_name.ref = msg_origport(msg);
	tsock->peer_name.node = msg_orignode(msg);
	p_ptr = tipc_port_deref(tsock->p->ref);
	if (!p_ptr)
		return -EINVAL;

	__tipc_connect(tsock->p->ref, p_ptr, &tsock->peer_name);

	if (msg_importance(msg) > TIPC_CRITICAL_IMPORTANCE)
		return -EINVAL;
	msg_set_importance(&p_ptr->phdr, (u32)msg_importance(msg));
	sock->state = SS_CONNECTED;
	return 0;
}
