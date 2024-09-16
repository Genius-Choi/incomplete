rpc_free_client(struct rpc_clnt *clnt)
{
	dprintk("RPC:       destroying %s client for %s\n",
			clnt->cl_protname, clnt->cl_server);
	if (!IS_ERR(clnt->cl_path.dentry)) {
		rpc_remove_client_dir(clnt->cl_path.dentry);
		rpc_put_mount();
	}
	if (clnt->cl_parent != clnt) {
		rpc_release_client(clnt->cl_parent);
		goto out_free;
	}
	if (clnt->cl_server != clnt->cl_inline_name)
		kfree(clnt->cl_server);
out_free:
	rpc_unregister_client(clnt);
	rpc_free_iostats(clnt->cl_metrics);
	kfree(clnt->cl_principal);
	clnt->cl_metrics = NULL;
	xprt_put(clnt->cl_xprt);
	rpciod_down();
	kfree(clnt);
}
