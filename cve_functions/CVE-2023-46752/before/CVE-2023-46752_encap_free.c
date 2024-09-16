static void encap_free(struct bgp_attr_encap_subtlv *p)
{
	struct bgp_attr_encap_subtlv *next;
	while (p) {
		next = p->next;
		p->next = NULL;
		XFREE(MTYPE_ENCAP_TLV, p);
		p = next;
	}
}
