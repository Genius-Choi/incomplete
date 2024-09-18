void svc_shutdown_net(struct svc_serv *serv, struct net *net)
{
	svc_close_net(serv, net);

	if (serv->sv_ops->svo_shutdown)
		serv->sv_ops->svo_shutdown(serv, net);
}
