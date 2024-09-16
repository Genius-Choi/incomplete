static inline void fwnet_make_ff_hdr(struct rfc2734_header *hdr,
		unsigned ether_type, unsigned dg_size, unsigned dgl)
{
	hdr->w0 = fwnet_set_hdr_lf(RFC2374_HDR_FIRSTFRAG)
		  | fwnet_set_hdr_dg_size(dg_size)
		  | fwnet_set_hdr_ether_type(ether_type);
	hdr->w1 = fwnet_set_hdr_dgl(dgl);
}
