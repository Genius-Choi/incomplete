void bgp_attr_dup(struct attr *new, struct attr *orig)
{
	*new = *orig;
}
