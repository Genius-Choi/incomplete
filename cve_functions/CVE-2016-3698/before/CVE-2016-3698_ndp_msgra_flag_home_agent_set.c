void ndp_msgra_flag_home_agent_set(struct ndp_msgra *msgra,
				   bool flag_home_agent)
{
	if (flag_home_agent)
		msgra->ra->nd_ra_flags_reserved |= ND_RA_FLAG_HOME_AGENT;
	else
		msgra->ra->nd_ra_flags_reserved &= ~ND_RA_FLAG_HOME_AGENT;
}
