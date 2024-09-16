nfs4_get_existing_delegation(struct nfs4_client *clp, struct nfs4_file *fp)
{
	struct nfs4_delegation *searchdp = NULL;
	struct nfs4_client *searchclp = NULL;

	lockdep_assert_held(&state_lock);
	lockdep_assert_held(&fp->fi_lock);

	list_for_each_entry(searchdp, &fp->fi_delegations, dl_perfile) {
		searchclp = searchdp->dl_stid.sc_client;
		if (clp == searchclp) {
			return -EAGAIN;
		}
	}
	return 0;
}
