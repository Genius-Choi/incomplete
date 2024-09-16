nfsd_reap_openowners(struct list_head *reaplist)
{
	struct nfs4_client *clp;
	struct nfs4_openowner *oop, *next;

	list_for_each_entry_safe(oop, next, reaplist, oo_perclient) {
		list_del_init(&oop->oo_perclient);
		clp = oop->oo_owner.so_client;
		release_openowner(oop);
		put_client(clp);
	}
}
