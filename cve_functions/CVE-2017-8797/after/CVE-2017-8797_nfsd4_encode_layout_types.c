nfsd4_encode_layout_types(struct xdr_stream *xdr, u32 layout_types)
{
	__be32		*p;
	unsigned long	i = hweight_long(layout_types);

	p = xdr_reserve_space(xdr, 4 + 4 * i);
	if (!p)
		return nfserr_resource;

	*p++ = cpu_to_be32(i);

	for (i = LAYOUT_NFSV4_1_FILES; i < LAYOUT_TYPE_MAX; ++i)
		if (layout_types & (1 << i))
			*p++ = cpu_to_be32(i);

	return 0;
}
