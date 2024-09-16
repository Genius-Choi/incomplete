static struct nfs4_delegation *find_deleg_stateid(struct nfs4_client *cl, stateid_t *s)
{
	struct nfs4_stid *ret;

	ret = find_stateid_by_type(cl, s, NFS4_DELEG_STID);
	if (!ret)
		return NULL;
	return delegstateid(ret);
}
