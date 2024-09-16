static inline void fwnet_make_uf_hdr(struct rfc2734_header *hdr,
		unsigned ether_type)
{
	hdr->w0 = fwnet_set_hdr_lf(RFC2374_HDR_UNFRAG)
		  | fwnet_set_hdr_ether_type(ether_type);
}
