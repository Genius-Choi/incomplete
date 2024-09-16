void ndp_msgra_route_preference_set(struct ndp_msgra *msgra,
				    enum ndp_route_preference pref)
{
	msgra->ra->nd_ra_flags_reserved &= ~(3 << 3);
	msgra->ra->nd_ra_flags_reserved |= (pref << 3);
}
