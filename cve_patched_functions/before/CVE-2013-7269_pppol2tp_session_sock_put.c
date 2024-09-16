static void pppol2tp_session_sock_put(struct l2tp_session *session)
{
	struct pppol2tp_session *ps = l2tp_session_priv(session);

	if (ps->sock)
		sock_put(ps->sock);
}
