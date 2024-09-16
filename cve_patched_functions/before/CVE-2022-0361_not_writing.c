not_writing(void)
{
    if (p_write)
	return FALSE;
    emsg(_(e_file_not_written_writing_is_disabled_by_write_option));
    return TRUE;
}
