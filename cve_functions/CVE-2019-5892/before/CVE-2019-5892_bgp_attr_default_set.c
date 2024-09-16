struct attr *bgp_attr_default_set(struct attr *attr, uint8_t origin)
{
	memset(attr, 0, sizeof(struct attr));

	attr->origin = origin;
	attr->flag |= ATTR_FLAG_BIT(BGP_ATTR_ORIGIN);
	attr->aspath = aspath_empty();
	attr->flag |= ATTR_FLAG_BIT(BGP_ATTR_AS_PATH);
	attr->weight = BGP_ATTR_DEFAULT_WEIGHT;
	attr->tag = 0;
	attr->label_index = BGP_INVALID_LABEL_INDEX;
	attr->label = MPLS_INVALID_LABEL;
	attr->flag |= ATTR_FLAG_BIT(BGP_ATTR_NEXT_HOP);
	attr->mp_nexthop_len = IPV6_MAX_BYTELEN;

	return attr;
}
