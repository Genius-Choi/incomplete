static inline struct ip_tunnel **ipip_bucket(struct ipip_net *ipn,
		struct ip_tunnel *t)
{
	return __ipip_bucket(ipn, &t->parms);
}
