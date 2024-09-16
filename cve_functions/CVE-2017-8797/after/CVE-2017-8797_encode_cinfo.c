static __be32 *encode_cinfo(__be32 *p, struct nfsd4_change_info *c)
{
	*p++ = cpu_to_be32(c->atomic);
	if (c->change_supported) {
		p = xdr_encode_hyper(p, c->before_change);
		p = xdr_encode_hyper(p, c->after_change);
	} else {
		*p++ = cpu_to_be32(c->before_ctime_sec);
		*p++ = cpu_to_be32(c->before_ctime_nsec);
		*p++ = cpu_to_be32(c->after_ctime_sec);
		*p++ = cpu_to_be32(c->after_ctime_nsec);
	}
	return p;
}
