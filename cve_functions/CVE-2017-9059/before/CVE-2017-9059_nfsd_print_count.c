static void nfsd_print_count(struct nfs4_client *clp, unsigned int count,
			     const char *type)
{
	char buf[INET6_ADDRSTRLEN];
	rpc_ntop((struct sockaddr *)&clp->cl_addr, buf, sizeof(buf));
	printk(KERN_INFO "NFS Client: %s has %u %s\n", buf, count, type);
}
