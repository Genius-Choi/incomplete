struct rpc_cred *nfs4_get_renew_cred_locked(struct nfs_client *clp)
{
	struct nfs4_state_owner *sp;
	struct rb_node *pos;
	struct rpc_cred *cred = NULL;

	for (pos = rb_first(&clp->cl_state_owners); pos != NULL; pos = rb_next(pos)) {
		sp = rb_entry(pos, struct nfs4_state_owner, so_client_node);
		if (list_empty(&sp->so_states))
			continue;
		cred = get_rpccred(sp->so_cred);
		break;
	}
	return cred;
}
