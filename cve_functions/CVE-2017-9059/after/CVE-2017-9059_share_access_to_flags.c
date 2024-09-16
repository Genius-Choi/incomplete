static int share_access_to_flags(u32 share_access)
{
	return share_access == NFS4_SHARE_ACCESS_READ ? RD_STATE : WR_STATE;
}
