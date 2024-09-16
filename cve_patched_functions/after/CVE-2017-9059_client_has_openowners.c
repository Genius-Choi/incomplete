static bool client_has_openowners(struct nfs4_client *clp)
{
	struct nfs4_openowner *oo;

	list_for_each_entry(oo, &clp->cl_openowners, oo_perclient) {
		if (!list_empty(&oo->oo_owner.so_stateids))
			return true;
	}
	return false;
}
