set_script_uid_gid(vector_t *strvec, unsigned keyword_offset, uid_t *uid_p, gid_t *gid_p)
{
	char *username;
	char *groupname;

	username = strvec_slot(strvec, keyword_offset);
	if (vector_size(strvec) > keyword_offset + 1)
		groupname = strvec_slot(strvec, keyword_offset + 1);
	else
		groupname = NULL;

	return set_uid_gid(username, groupname, uid_p, gid_p, false);
}
