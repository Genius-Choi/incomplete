void ndp_msgra_flag_other_set(struct ndp_msgra *msgra, bool flag_other)
{
	if (flag_other)
		msgra->ra->nd_ra_flags_reserved |= ND_RA_FLAG_OTHER;
	else
		msgra->ra->nd_ra_flags_reserved &= ~ND_RA_FLAG_OTHER;
}
