void bgp_attr_flush(struct attr *attr)
{
	if (attr->aspath && !attr->aspath->refcnt) {
		aspath_free(attr->aspath);
		attr->aspath = NULL;
	}
	if (attr->community && !attr->community->refcnt)
		community_free(&attr->community);
	if (attr->ecommunity && !attr->ecommunity->refcnt)
		ecommunity_free(&attr->ecommunity);
	if (attr->lcommunity && !attr->lcommunity->refcnt)
		lcommunity_free(&attr->lcommunity);
	if (attr->cluster && !attr->cluster->refcnt) {
		cluster_free(attr->cluster);
		attr->cluster = NULL;
	}
	if (attr->transit && !attr->transit->refcnt) {
		transit_free(attr->transit);
		attr->transit = NULL;
	}
	if (attr->encap_subtlvs && !attr->encap_subtlvs->refcnt) {
		encap_free(attr->encap_subtlvs);
		attr->encap_subtlvs = NULL;
	}
#if ENABLE_BGP_VNC
	if (attr->vnc_subtlvs && !attr->vnc_subtlvs->refcnt) {
		encap_free(attr->vnc_subtlvs);
		attr->vnc_subtlvs = NULL;
	}
#endif
}
