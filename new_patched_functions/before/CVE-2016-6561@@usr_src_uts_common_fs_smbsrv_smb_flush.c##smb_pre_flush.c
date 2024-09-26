smb_pre_flush(smb_request_t *sr)
{
	int rc;

	rc = smbsr_decode_vwv(sr, "w", &sr->smb_fid);

	DTRACE_SMB_1(op__Flush__start, smb_request_t *, sr);

	return ((rc == 0) ? SDRC_SUCCESS : SDRC_ERROR);
}
