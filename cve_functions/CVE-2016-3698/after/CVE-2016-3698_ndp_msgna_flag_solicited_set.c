void ndp_msgna_flag_solicited_set(struct ndp_msgna *msgna, bool flag_solicited)
{
	if (flag_solicited)
		msgna->na->nd_na_flags_reserved |= ND_NA_FLAG_SOLICITED;
	else
		msgna->na->nd_na_flags_reserved &= ~ND_NA_FLAG_SOLICITED;
}
