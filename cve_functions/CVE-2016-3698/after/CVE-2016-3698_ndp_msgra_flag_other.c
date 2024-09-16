bool ndp_msgra_flag_other(struct ndp_msgra *msgra)
{
	return msgra->ra->nd_ra_flags_reserved & ND_RA_FLAG_OTHER;
}
