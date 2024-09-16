uint16_t ndp_msgra_router_lifetime(struct ndp_msgra *msgra)
{
	return ntohs(msgra->ra->nd_ra_router_lifetime);
}
