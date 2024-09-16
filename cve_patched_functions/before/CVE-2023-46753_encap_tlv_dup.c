struct bgp_attr_encap_subtlv *encap_tlv_dup(struct bgp_attr_encap_subtlv *orig)
{
	struct bgp_attr_encap_subtlv *new;
	struct bgp_attr_encap_subtlv *tail;
	struct bgp_attr_encap_subtlv *p;

	for (p = orig, tail = new = NULL; p; p = p->next) {
		int size = sizeof(struct bgp_attr_encap_subtlv) + p->length;
		if (tail) {
			tail->next = XCALLOC(MTYPE_ENCAP_TLV, size);
			tail = tail->next;
		} else {
			tail = new = XCALLOC(MTYPE_ENCAP_TLV, size);
		}
		assert(tail);
		memcpy(tail, p, size);
		tail->next = NULL;
	}

	return new;
}
