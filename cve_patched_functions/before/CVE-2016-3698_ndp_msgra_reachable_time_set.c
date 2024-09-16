void ndp_msgra_reachable_time_set(struct ndp_msgra *msgra,
				  uint32_t reachable_time)
{
	msgra->ra->nd_ra_reachable = htonl(reachable_time);
}
