static void unhash_openowner_locked(struct nfs4_openowner *oo)
{
	struct nfs4_client *clp = oo->oo_owner.so_client;

	lockdep_assert_held(&clp->cl_lock);

	list_del_init(&oo->oo_owner.so_strhash);
	list_del_init(&oo->oo_perclient);
}
