int nfs4_open_delegation_recall(struct nfs_open_context *ctx, struct nfs4_state *state, const nfs4_stateid *stateid)
{
	struct nfs_server *server = NFS_SERVER(state->inode);
	struct nfs4_opendata *opendata;
	int err;

	opendata = nfs4_open_recoverdata_alloc(ctx, state,
			NFS4_OPEN_CLAIM_DELEG_CUR_FH);
	if (IS_ERR(opendata))
		return PTR_ERR(opendata);
	nfs4_stateid_copy(&opendata->o_arg.u.delegation, stateid);
	err = nfs4_open_recover(opendata, state);
	nfs4_opendata_put(opendata);
	return nfs4_handle_delegation_recall_error(server, state, stateid, err);
}
