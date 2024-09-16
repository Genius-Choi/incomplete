nfsd_inject_print_clients(void)
{
	struct nfs4_client *clp;
	u64 count = 0;
	struct nfsd_net *nn = net_generic(current->nsproxy->net_ns,
					  nfsd_net_id);
	char buf[INET6_ADDRSTRLEN];

	if (!nfsd_netns_ready(nn))
		return 0;

	spin_lock(&nn->client_lock);
	list_for_each_entry(clp, &nn->client_lru, cl_lru) {
		rpc_ntop((struct sockaddr *)&clp->cl_addr, buf, sizeof(buf));
		pr_info("NFS Client: %s\n", buf);
		++count;
	}
	spin_unlock(&nn->client_lock);

	return count;
}
