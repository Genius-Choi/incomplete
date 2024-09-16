test_access(u32 access, struct nfs4_ol_stateid *stp)
{
	unsigned char mask = 1 << access;

	return (bool)(stp->st_access_bmap & mask);
}
