int sock_create_kern(struct net *net, int family, int type, int protocol, struct socket **res)
{
	return __sock_create(net, family, type, protocol, res, 1);
}
