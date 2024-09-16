find_stateid_locked(struct nfs4_client *cl, stateid_t *t)
{
	struct nfs4_stid *ret;

	ret = idr_find(&cl->cl_stateids, t->si_opaque.so_id);
	if (!ret || !ret->sc_type)
		return NULL;
	return ret;
}
