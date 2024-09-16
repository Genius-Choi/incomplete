smb_ofile_is_open_locked(smb_ofile_t *of)
{
	switch (of->f_state) {
	case SMB_OFILE_STATE_OPEN:
		return (B_TRUE);

	case SMB_OFILE_STATE_CLOSING:
	case SMB_OFILE_STATE_CLOSED:
		return (B_FALSE);

	default:
		ASSERT(0);
		return (B_FALSE);
	}
}
