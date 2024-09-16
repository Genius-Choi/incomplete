nfsd_find_client(struct sockaddr_storage *addr, size_t addr_size)
{
	struct nfs4_client *clp;
	struct nfsd_net *nn = net_generic(current->nsproxy->net_ns,
					  nfsd_net_id);

	if (!nfsd_netns_ready(nn))
		return NULL;

	list_for_each_entry(clp, &nn->client_lru, cl_lru) {
		if (memcmp(&clp->cl_addr, addr, addr_size) == 0)
			return clp;
	}
	return NULL;
}
