static void maybe_add_creds(struct sk_buff *skb, const struct socket *sock,
			    const struct sock *other)
{
	if (UNIXCB(skb).cred)
		return;
	if (test_bit(SOCK_PASSCRED, &sock->flags) ||
	    !other->sk_socket ||
	    test_bit(SOCK_PASSCRED, &other->sk_socket->flags)) {
		UNIXCB(skb).pid  = get_pid(task_tgid(current));
		UNIXCB(skb).cred = get_current_cred();
	}
}
