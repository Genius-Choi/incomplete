nfsd4_fl_put_owner(fl_owner_t owner)
{
	struct nfs4_lockowner *lo = (struct nfs4_lockowner *)owner;

	if (lo)
		nfs4_put_stateowner(&lo->lo_owner);
}
