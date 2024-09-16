__be32 nfs4_acl_write_who(struct xdr_stream *xdr, int who)
{
	__be32 *p;
	int i;

	for (i = 0; i < ARRAY_SIZE(s2t_map); i++) {
		if (s2t_map[i].type != who)
			continue;
		p = xdr_reserve_space(xdr, s2t_map[i].stringlen + 4);
		if (!p)
			return nfserr_resource;
		p = xdr_encode_opaque(p, s2t_map[i].string,
					s2t_map[i].stringlen);
		return 0;
	}
	WARN_ON_ONCE(1);
	return nfserr_serverfault;
}
