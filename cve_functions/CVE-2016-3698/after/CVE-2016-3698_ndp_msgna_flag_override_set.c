void ndp_msgna_flag_override_set(struct ndp_msgna *msgna, bool flag_override)
{
	if (flag_override)
		msgna->na->nd_na_flags_reserved |= ND_NA_FLAG_OVERRIDE;
	else
		msgna->na->nd_na_flags_reserved &= ~ND_NA_FLAG_OVERRIDE;
}
