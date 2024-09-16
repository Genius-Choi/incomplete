vrrp_tfile_handler(vector_t *strvec)
{
	if (!strvec)
		return;

	alloc_vrrp_file(strvec_slot(strvec, 1));

	track_file_init = TRACK_FILE_NO_INIT;
}
