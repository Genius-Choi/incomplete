static void nfs4_unhash_openowner(struct nfs4_stateowner *so)
{
	unhash_openowner_locked(openowner(so));
}
