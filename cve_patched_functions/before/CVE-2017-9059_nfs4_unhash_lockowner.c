static void nfs4_unhash_lockowner(struct nfs4_stateowner *sop)
{
	unhash_lockowner_locked(lockowner(sop));
}
