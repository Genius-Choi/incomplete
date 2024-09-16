void ndp_msgna_flag_router_set(struct ndp_msgna *msgna, bool flag_router)
{
	if (flag_router)
		msgna->na->nd_na_flags_reserved |= ND_NA_FLAG_ROUTER;
	else
		msgna->na->nd_na_flags_reserved &= ~ND_NA_FLAG_ROUTER;
}
