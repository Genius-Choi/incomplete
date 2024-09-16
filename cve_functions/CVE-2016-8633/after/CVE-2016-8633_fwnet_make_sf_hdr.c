static inline void fwnet_make_sf_hdr(struct rfc2734_header *hdr,
		unsigned lf, unsigned dg_size, unsigned fg_off, unsigned dgl)
{
	hdr->w0 = fwnet_set_hdr_lf(lf)
		  | fwnet_set_hdr_dg_size(dg_size)
		  | fwnet_set_hdr_fg_off(fg_off);
	hdr->w1 = fwnet_set_hdr_dgl(dgl);
}
