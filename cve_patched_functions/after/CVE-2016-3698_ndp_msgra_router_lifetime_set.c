void ndp_msgra_router_lifetime_set(struct ndp_msgra *msgra,
				   uint16_t router_lifetime)
{
	msgra->ra->nd_ra_router_lifetime = htons(router_lifetime);
}
