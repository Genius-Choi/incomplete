smb_ofile_share_check(smb_ofile_t *of)
{
	return (!SMB_DENY_ALL(of->f_share_access));
}
