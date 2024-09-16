static int size_of_ntlmssp_blob(struct cifs_ses *ses)
{
	int sz = sizeof(AUTHENTICATE_MESSAGE) + ses->auth_key.len
		- CIFS_SESS_KEY_SIZE + CIFS_CPHTXT_SIZE + 2;

	if (ses->domainName)
		sz += 2 * strnlen(ses->domainName, CIFS_MAX_DOMAINNAME_LEN);
	else
		sz += 2;

	if (ses->user_name)
		sz += 2 * strnlen(ses->user_name, CIFS_MAX_USERNAME_LEN);
	else
		sz += 2;

	return sz;
}
