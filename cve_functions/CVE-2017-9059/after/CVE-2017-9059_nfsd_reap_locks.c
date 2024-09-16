nfsd_reap_locks(struct list_head *reaplist)
{
	struct nfs4_client *clp;
	struct nfs4_ol_stateid *stp, *next;

	list_for_each_entry_safe(stp, next, reaplist, st_locks) {
		list_del_init(&stp->st_locks);
		clp = stp->st_stid.sc_client;
		nfs4_put_stid(&stp->st_stid);
		put_client(clp);
	}
}
