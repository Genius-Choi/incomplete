smb_ofile_set_quota_resume(smb_ofile_t *ofile, char *resume)
{
	ASSERT(ofile);
	mutex_enter(&ofile->f_mutex);
	if (resume == NULL)
		bzero(ofile->f_quota_resume, SMB_SID_STRSZ);
	else
		(void) strlcpy(ofile->f_quota_resume, resume, SMB_SID_STRSZ);
	mutex_exit(&ofile->f_mutex);
}
