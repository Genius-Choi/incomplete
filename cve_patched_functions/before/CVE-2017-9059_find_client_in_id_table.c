find_client_in_id_table(struct list_head *tbl, clientid_t *clid, bool sessions)
{
	struct nfs4_client *clp;
	unsigned int idhashval = clientid_hashval(clid->cl_id);

	list_for_each_entry(clp, &tbl[idhashval], cl_idhash) {
		if (same_clid(&clp->cl_clientid, clid)) {
			if ((bool)clp->cl_minorversion != sessions)
				return NULL;
			renew_client_locked(clp);
			return clp;
		}
	}
	return NULL;
}
