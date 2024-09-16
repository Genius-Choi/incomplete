nfsd4_fl_get_owner(fl_owner_t owner)
{
	struct nfs4_lockowner *lo = (struct nfs4_lockowner *)owner;

	nfs4_get_stateowner(&lo->lo_owner);
	return owner;
}
