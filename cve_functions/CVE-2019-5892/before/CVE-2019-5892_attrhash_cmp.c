bool attrhash_cmp(const void *p1, const void *p2)
{
	const struct attr *attr1 = p1;
	const struct attr *attr2 = p2;

	if (attr1->flag == attr2->flag && attr1->origin == attr2->origin
	    && attr1->nexthop.s_addr == attr2->nexthop.s_addr
	    && attr1->aspath == attr2->aspath
	    && attr1->community == attr2->community && attr1->med == attr2->med
	    && attr1->local_pref == attr2->local_pref
	    && attr1->rmap_change_flags == attr2->rmap_change_flags) {
		if (attr1->aggregator_as == attr2->aggregator_as
		    && attr1->aggregator_addr.s_addr
			       == attr2->aggregator_addr.s_addr
		    && attr1->weight == attr2->weight
		    && attr1->tag == attr2->tag
		    && attr1->label_index == attr2->label_index
		    && attr1->mp_nexthop_len == attr2->mp_nexthop_len
		    && attr1->ecommunity == attr2->ecommunity
		    && attr1->lcommunity == attr2->lcommunity
		    && attr1->cluster == attr2->cluster
		    && attr1->transit == attr2->transit
		    && (attr1->encap_tunneltype == attr2->encap_tunneltype)
		    && encap_same(attr1->encap_subtlvs, attr2->encap_subtlvs)
#if ENABLE_BGP_VNC
		    && encap_same(attr1->vnc_subtlvs, attr2->vnc_subtlvs)
#endif
		    && IPV6_ADDR_SAME(&attr1->mp_nexthop_global,
				      &attr2->mp_nexthop_global)
		    && IPV6_ADDR_SAME(&attr1->mp_nexthop_local,
				      &attr2->mp_nexthop_local)
		    && IPV4_ADDR_SAME(&attr1->mp_nexthop_global_in,
				      &attr2->mp_nexthop_global_in)
		    && IPV4_ADDR_SAME(&attr1->originator_id,
				      &attr2->originator_id)
		    && overlay_index_same(attr1, attr2)
		    && attr1->nh_ifindex == attr2->nh_ifindex
		    && attr1->nh_lla_ifindex == attr2->nh_lla_ifindex)
			return true;
	}

	return false;
}
