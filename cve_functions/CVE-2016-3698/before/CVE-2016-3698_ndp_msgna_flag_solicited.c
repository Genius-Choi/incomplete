bool ndp_msgna_flag_solicited(struct ndp_msgna *msgna)
{
	return msgna->na->nd_na_flags_reserved & ND_NA_FLAG_SOLICITED;
}
