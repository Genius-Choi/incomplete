nfsd4_init_slabs(void)
{
	openowner_slab = kmem_cache_create("nfsd4_openowners",
			sizeof(struct nfs4_openowner), 0, 0, NULL);
	if (openowner_slab == NULL)
		goto out;
	lockowner_slab = kmem_cache_create("nfsd4_lockowners",
			sizeof(struct nfs4_lockowner), 0, 0, NULL);
	if (lockowner_slab == NULL)
		goto out_free_openowner_slab;
	file_slab = kmem_cache_create("nfsd4_files",
			sizeof(struct nfs4_file), 0, 0, NULL);
	if (file_slab == NULL)
		goto out_free_lockowner_slab;
	stateid_slab = kmem_cache_create("nfsd4_stateids",
			sizeof(struct nfs4_ol_stateid), 0, 0, NULL);
	if (stateid_slab == NULL)
		goto out_free_file_slab;
	deleg_slab = kmem_cache_create("nfsd4_delegations",
			sizeof(struct nfs4_delegation), 0, 0, NULL);
	if (deleg_slab == NULL)
		goto out_free_stateid_slab;
	odstate_slab = kmem_cache_create("nfsd4_odstate",
			sizeof(struct nfs4_clnt_odstate), 0, 0, NULL);
	if (odstate_slab == NULL)
		goto out_free_deleg_slab;
	return 0;

out_free_deleg_slab:
	kmem_cache_destroy(deleg_slab);
out_free_stateid_slab:
	kmem_cache_destroy(stateid_slab);
out_free_file_slab:
	kmem_cache_destroy(file_slab);
out_free_lockowner_slab:
	kmem_cache_destroy(lockowner_slab);
out_free_openowner_slab:
	kmem_cache_destroy(openowner_slab);
out:
	dprintk("nfsd4: out of memory while initializing nfsv4\n");
	return -ENOMEM;
}
