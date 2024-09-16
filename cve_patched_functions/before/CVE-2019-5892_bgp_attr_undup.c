void bgp_attr_undup(struct attr *new, struct attr *old)
{
	if (new->aspath != old->aspath)
		aspath_free(new->aspath);

	if (new->community != old->community)
		community_free(&new->community);

	if (new->ecommunity != old->ecommunity)
		ecommunity_free(&new->ecommunity);

	if (new->lcommunity != old->lcommunity)
		lcommunity_free(&new->lcommunity);
}
