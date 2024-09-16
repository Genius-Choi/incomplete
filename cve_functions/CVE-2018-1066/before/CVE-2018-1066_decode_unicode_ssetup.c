decode_unicode_ssetup(char **pbcc_area, int bleft, struct cifs_ses *ses,
		      const struct nls_table *nls_cp)
{
	int len;
	char *data = *pbcc_area;

	cifs_dbg(FYI, "bleft %d\n", bleft);

	kfree(ses->serverOS);
	ses->serverOS = cifs_strndup_from_utf16(data, bleft, true, nls_cp);
	cifs_dbg(FYI, "serverOS=%s\n", ses->serverOS);
	len = (UniStrnlen((wchar_t *) data, bleft / 2) * 2) + 2;
	data += len;
	bleft -= len;
	if (bleft <= 0)
		return;

	kfree(ses->serverNOS);
	ses->serverNOS = cifs_strndup_from_utf16(data, bleft, true, nls_cp);
	cifs_dbg(FYI, "serverNOS=%s\n", ses->serverNOS);
	len = (UniStrnlen((wchar_t *) data, bleft / 2) * 2) + 2;
	data += len;
	bleft -= len;
	if (bleft <= 0)
		return;

	kfree(ses->serverDomain);
	ses->serverDomain = cifs_strndup_from_utf16(data, bleft, true, nls_cp);
	cifs_dbg(FYI, "serverDomain=%s\n", ses->serverDomain);

	return;
}
