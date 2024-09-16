smb_ofile_set_delete_on_close(smb_ofile_t *of)
{
	mutex_enter(&of->f_mutex);
	of->f_flags |= SMB_OFLAGS_SET_DELETE_ON_CLOSE;
	mutex_exit(&of->f_mutex);
}
