static int nfs_callback_up_net(int minorversion, struct svc_serv *serv,
			       struct net *net, struct rpc_xprt *xprt)
{
	struct nfs_net *nn = net_generic(net, nfs_net_id);
	int ret;

	if (nn->cb_users[minorversion]++)
		return 0;

	dprintk("NFS: create per-net callback data; net=%p\n", net);

	ret = svc_bind(serv, net);
	if (ret < 0) {
		printk(KERN_WARNING "NFS: bind callback service failed\n");
		goto err_bind;
	}

	ret = -EPROTONOSUPPORT;
	if (!IS_ENABLED(CONFIG_NFS_V4_1) || minorversion == 0)
		ret = nfs4_callback_up_net(serv, net);
	else if (xprt->ops->bc_up)
		ret = xprt->ops->bc_up(serv, net);

	if (ret < 0) {
		printk(KERN_ERR "NFS: callback service start failed\n");
		goto err_socks;
	}
	return 0;

err_socks:
	svc_rpcb_cleanup(serv, net);
err_bind:
	nn->cb_users[minorversion]--;
	dprintk("NFS: Couldn't create callback socket: err = %d; "
			"net = %p\n", ret, net);
	return ret;
}
