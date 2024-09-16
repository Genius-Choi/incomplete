static inline int netlink_capable(const struct socket *sock, unsigned int flag)
{
	return (nl_table[sock->sk->sk_protocol].nl_nonroot & flag) ||
	       capable(CAP_NET_ADMIN);
}
