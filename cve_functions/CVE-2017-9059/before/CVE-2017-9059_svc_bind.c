int svc_bind(struct svc_serv *serv, struct net *net)
{
	if (!svc_uses_rpcbind(serv))
		return 0;
	return svc_rpcb_setup(serv, net);
}
