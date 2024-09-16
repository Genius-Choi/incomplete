static int cipso_v4_gentag_loc(const struct cipso_v4_doi *doi_def,
			       const struct netlbl_lsm_secattr *secattr,
			       unsigned char *buffer,
			       u32 buffer_len)
{
	if (!(secattr->flags & NETLBL_SECATTR_SECID))
		return -EPERM;

	buffer[0] = CIPSO_V4_TAG_LOCAL;
	buffer[1] = CIPSO_V4_TAG_LOC_BLEN;
	*(u32 *)&buffer[2] = secattr->attr.secid;

	return CIPSO_V4_TAG_LOC_BLEN;
}
