smb_ofile_get_quota_resume(smb_ofile_t *ofile, char *buf, int bufsize)
{
	ASSERT(ofile);
	mutex_enter(&ofile->f_mutex);
	(void) strlcpy(buf, ofile->f_quota_resume, bufsize);
	mutex_exit(&ofile->f_mutex);
}
