static void *bgp_attr_hash_alloc(void *p)
{
	struct attr *val = (struct attr *)p;
	struct attr *attr;

	attr = XMALLOC(MTYPE_ATTR, sizeof(struct attr));
	*attr = *val;
	if (val->encap_subtlvs) {
		val->encap_subtlvs = NULL;
	}
#if ENABLE_BGP_VNC
	if (val->vnc_subtlvs) {
		val->vnc_subtlvs = NULL;
	}
#endif
	attr->refcnt = 0;
	return attr;
}
