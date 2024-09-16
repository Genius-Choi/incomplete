smb_ofile_hold(smb_ofile_t *of)
{
	ASSERT(of);
	ASSERT(of->f_magic == SMB_OFILE_MAGIC);

	mutex_enter(&of->f_mutex);

	if (of->f_state != SMB_OFILE_STATE_OPEN) {
		mutex_exit(&of->f_mutex);
		return (B_FALSE);
	}
	of->f_refcnt++;

	mutex_exit(&of->f_mutex);
	return (B_TRUE);
}
