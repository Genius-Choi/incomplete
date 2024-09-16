static int cipso_v4_parsetag_loc(const struct cipso_v4_doi *doi_def,
				 const unsigned char *tag,
				 struct netlbl_lsm_secattr *secattr)
{
	secattr->attr.secid = *(u32 *)&tag[2];
	secattr->flags |= NETLBL_SECATTR_SECID;

	return 0;
}
