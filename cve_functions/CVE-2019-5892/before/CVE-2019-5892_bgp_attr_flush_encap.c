void bgp_attr_flush_encap(struct attr *attr)
{
	if (!attr)
		return;

	if (attr->encap_subtlvs) {
		encap_free(attr->encap_subtlvs);
		attr->encap_subtlvs = NULL;
	}
#if ENABLE_BGP_VNC
	if (attr->vnc_subtlvs) {
		encap_free(attr->vnc_subtlvs);
		attr->vnc_subtlvs = NULL;
	}
#endif
}
