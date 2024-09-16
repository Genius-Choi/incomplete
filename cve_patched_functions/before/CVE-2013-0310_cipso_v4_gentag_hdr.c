static void cipso_v4_gentag_hdr(const struct cipso_v4_doi *doi_def,
				unsigned char *buf,
				u32 len)
{
	buf[0] = IPOPT_CIPSO;
	buf[1] = CIPSO_V4_HDR_LEN + len;
	*(__be32 *)&buf[2] = htonl(doi_def->doi);
}
