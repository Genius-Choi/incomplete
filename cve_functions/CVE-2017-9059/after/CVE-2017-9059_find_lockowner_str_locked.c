find_lockowner_str_locked(struct nfs4_client *clp, struct xdr_netobj *owner)
{
	unsigned int strhashval = ownerstr_hashval(owner);
	struct nfs4_stateowner *so;

	lockdep_assert_held(&clp->cl_lock);

	list_for_each_entry(so, &clp->cl_ownerstr_hashtbl[strhashval],
			    so_strhash) {
		if (so->so_is_open_owner)
			continue;
		if (same_owner_str(so, owner))
			return lockowner(nfs4_get_stateowner(so));
	}
	return NULL;
}
